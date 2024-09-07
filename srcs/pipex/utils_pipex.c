/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:21:03 by roespici          #+#    #+#             */
/*   Updated: 2024/09/07 15:23:35 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_exit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int	open_infile(t_pipex *pipex)
{
	if (pipex->cmd->redir->token == IN)
	{
		pipex->infile = open(pipex->cmd->redir->element, O_RDONLY);
		if (access(pipex->cmd->redir->element, F_OK) == FAILURE)
		{
			pipex->infile_open = 0;
			pipex->nb_pipes--;
			ft_printf("bash: %s: No such file or directory\n", \
				pipex->cmd->redir->element);
			return (FAILURE);
		}
		if (access(pipex->cmd->redir->element, X_OK) == FAILURE)
		{
			pipex->infile_open = 0;
			pipex->nb_pipes--;
			ft_printf("bash: %s: Permission denied\n", \
				pipex->cmd->redir->element);
			return (FAILURE);
		}
		return (SUCCESS);
	}
}

int	open_outfile(t_pipex *pipex)
{
	if (pipex->cmd->redir->token == OUT || pipex->cmd->redir->token == APPEND)
	{
		if (pipex->cmd->redir->token == OUT)
			pipex->outfile = open(pipex->cmd->redir->element, \
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (pipex->cmd->redir->token == APPEND)
			pipex->outfile = open(pipex->cmd->redir->element, \
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (access(pipex->cmd->redir->element, W_OK) == FAILURE)
		{
			pipex->outfile_open = 0;
			if (pipex->infile_open)
				pipex->nb_pipes--;
			printf("bash: %s: Permission denied\n", pipex->cmd->redir->element);
			return (FAILURE);
		}
	}
	return (SUCCESS);
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
