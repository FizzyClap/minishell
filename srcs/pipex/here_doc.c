#include "../../includes/minishell.h"

static void	fill_here_doc(t_pipex *pipex);
static int	exec_here_doc(t_pipex *pipex, t_lexer *last_heredoc);

void	here_doc(t_pipex *pipex, t_lexer *redir)
{
	t_lexer	*last;

	last = find_last_redir(pipex->cmd, HEREDOC);
	pipex->limiter = ft_strdup(redir->element);
	fill_here_doc(pipex);
	if (redir != last)
	{
		free(pipex->limiter);
		unlink("here_doc.tmp");
		return ;
	}
	if (open_outfile(pipex) == FAILURE)
	{
		free(pipex->limiter);
		unlink("here_doc.tmp");
		return ;
	}
	if (exec_here_doc(pipex, last) == FAILURE)
		return ;
	close_pipes(pipex);
	free(pipex->limiter);
	unlink("here_doc.tmp");
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
		if (ft_strcmp(line, pipex->limiter) == 10)
		{
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
		free(pipex->limiter);
		unlink("here_doc.tmp");
		return (FAILURE);
	}
	if (!pipex->cmd->cmd)
	{
		free(pipex->limiter);
		return (FAILURE);
	}
	execute_pipes(pipex);
	return (SUCCESS);
}
