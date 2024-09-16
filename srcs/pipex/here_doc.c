#include "../../includes/minishell.h"

static void	fill_here_doc(t_pipex *pipex);
static int	exec_here_doc(t_pipex *pipex, t_lexer *last_heredoc);
static void	close_here_doc(t_pipex *pipex);

void	here_doc(t_pipex *pipex, t_lexer *redir)
{
	t_lexer	*last;

	last = find_last_redir(pipex->cmd, HEREDOC);
	pipex->limiter = ft_strdup(redir->element);
	fill_here_doc(pipex);
	if (redir != last)
	{
		close_here_doc(pipex);
		return ;
	}
	if (open_outfile(pipex) == FAILURE)
	{
		close_here_doc(pipex);
		return ;
	}
	if (exec_here_doc(pipex, last) == FAILURE)
		return ;
	close_pipes(pipex);
	close_here_doc(pipex);
}

static void	fill_here_doc(t_pipex *pipex)
{
	char	*line;

	here_signals();
	pipex->infile = open("here_doc.tmp", O_CREAT | O_WRONLY, 0644);
	if (pipex->infile < 0)
		error_exit("here_doc");
	while (1)
	{
		ft_putstr("> ");
		line = get_next_line(STDIN_FILENO);
		if (!line || ft_strcmp(line, pipex->limiter) == 10)
		{
			if (!line)
				printf("\n");
			free(line);
			break ;
		}
		ft_putstr_fd(line, pipex->infile);
		free(line);
	}
	close(pipex->infile);
}

static int	exec_here_doc(t_pipex *pipex, t_lexer *last_heredoc)
{
	if (ft_strcmp(pipex->last_infile->element, last_heredoc->element) == 0)
		pipex->infile = open("here_doc.tmp", O_RDONLY);
	else
	{
		close_here_doc(pipex);
		return (FAILURE);
	}
	if (!pipex->cmd->cmd)
	{
		close_here_doc(pipex);
		exit(EXIT_SUCCESS);
	}
	execute_pipes(pipex);
	return (SUCCESS);
}

static void	close_here_doc(t_pipex *pipex)
{
	free(pipex->limiter);
	unlink("here_doc.tmp");
}
