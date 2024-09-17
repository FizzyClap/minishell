/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:05:10 by roespici          #+#    #+#             */
/*   Updated: 2024/09/17 14:05:11 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_exit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

pid_t	fork_child(void)
{
	pid_t	child;

	child = fork();
	if (child == FAILURE)
		error_exit("Fork error");
	return (child);
}

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->nb_pipes)
	{
		close(pipex->pipefd[i][0]);
		close(pipex->pipefd[i][1]);
	}
}

void	free_pipex(t_pipex *pipex)
{
	int	i;

	if (pipex->nb_pipes > 0)
		close_pipes(pipex);
	i = -1;
	if (pipex->nb_pipes)
	{
		while (++i < pipex->nb_pipes)
		{
			free(pipex->pipefd[i]);
			pipex->pipefd[i] = NULL;
		}
	}
	free(pipex->pipefd);
	free(pipex->child);
	free(pipex);
}

t_lexer	*find_last_redir(t_cmd *cmd, int token)
{
	t_lexer	*last;
	t_lexer	*redir;

	last = NULL;
	redir = cmd->redir;
	while (redir)
	{
		if (token == OUT)
		{
			if (redir->token == OUT || redir->token == APPEND)
				last = redir;
		}
		else if (token == IN)
		{
			if (redir->token == IN || redir->token == HEREDOC)
				last = redir;
		}
		else if (token == HEREDOC)
		{
			if (redir->token == token)
				last = redir;
		}
		redir = redir->next;
	}
	return (last);
}
