/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartan <gartan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:21:03 by roespici          #+#    #+#             */
/*   Updated: 2024/09/09 17:27:11 by gartan           ###   ########.fr       */
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
	if (pipex->cmd->redir && pipex->cmd->redir->token && pipex->cmd->redir->token == IN)
	{
		pipex->infile = open(pipex->cmd->redir->element, O_RDONLY);
		if (access(pipex->cmd->redir->element, F_OK) == FAILURE)
		{
			pipex->nb_pipes--;
			ft_printf("bash: %s: No such file or directory\n", \
				pipex->cmd->redir->element);
			return (FAILURE);
		}
		else if (access(pipex->cmd->redir->element, R_OK) == FAILURE)
		{
			pipex->nb_pipes--;
			ft_printf("bash: %s: Permission denied\n", \
				pipex->cmd->redir->element);
			return (FAILURE);
		}
		pipex->infile_open = 1;
		pipex->infile_exist = 1;
	}
	else
		return (FAILURE);
	//if (pipex->cmd->redir->next)
	//{
	//	pipex->cmd->redir = pipex->cmd->redir->next;
	//	open_infile(pipex);
	//}
	return (SUCCESS);
}

int	open_outfile(t_pipex *pipex)
{
	if (pipex->cmd->redir && pipex->cmd->redir->token && \
		(pipex->cmd->redir->token == OUT || pipex->cmd->redir->token == APPEND))
	{
		if (pipex->cmd->redir->token == OUT)
			pipex->outfile = open(pipex->cmd->redir->element, \
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (pipex->cmd->redir->token == APPEND)
			pipex->outfile = open(pipex->cmd->redir->element, \
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (access(pipex->cmd->redir->element, W_OK) == FAILURE)
		{
			if (pipex->infile_open)
				pipex->nb_pipes--;
			if (pipex->limiter)
				return (FAILURE);
			printf("bash: %s: Permission denied\n", pipex->cmd->redir->element);
			return (FAILURE);
		}
		pipex->outfile_open = 1;
	}
	else
		return (FAILURE);
	//if (pipex->cmd->redir->next)
	//{
		//pipex->cmd->redir = pipex->cmd->redir->next;
		//open_outfile(pipex);
	//}
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

void	free_pipex(t_pipex *pipex)
{
	int	i;

	if (pipex->nb_pipes > 0)
		close_pipes(pipex);
	i = -1;
	if ((!pipex->infile_open || !pipex->outfile_open) && pipex->nb_pipes)
	{
		while (++i <= pipex->nb_pipes)
		{
			free(pipex->pipefd[i]);
			pipex->pipefd[i] = NULL;
		}
	}
	else if (pipex->nb_pipes)
	{
		while (++i < pipex->nb_pipes)
		{
			free(pipex->pipefd[i]);
			pipex->pipefd[i] = NULL;
		}
	}
	free(pipex->pipefd);
	free(pipex->child);
}
