/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:04:51 by roespici          #+#    #+#             */
/*   Updated: 2024/09/17 14:08:52 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	fill_here_doc(t_pipex *pipex);
static void	brut_stop(t_pipex *pipex, char *line, int index);
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
	int		index;

	here_signals();
	pipex->infile = open("here_doc.tmp", O_CREAT | O_WRONLY, 0644);
	if (pipex->infile < 0)
		error_exit("here_doc");
	index = 0;
	while (++index)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, pipex->limiter) == 0)
		{
			brut_stop(pipex, line, index);
			free(line);
			break ;
		}
		ft_putstr_fd(line, pipex->infile);
		free(line);
	}
	close(pipex->infile);
}

static void	brut_stop(t_pipex *pipex, char *line, int index)
{
	if (!line)
	{
		ft_fprintf(STDERR_FILENO, "Fraudistan: warning: here-document at line "\
		"%d delimited by end-of-file (wanted `%s')\n", index, pipex->limiter);
	}
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
