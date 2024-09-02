/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:41:50 by roespici          #+#    #+#             */
/*   Updated: 2024/09/02 07:36:14 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_pipex(t_pipex *pipex)
{
	int	i;

	if (pipex->nb_pipes > 0)
		close_pipes(pipex);
	i = -1;
	if (!pipex->infile_open || !pipex->outfile_open)
	{
		while (++i <= pipex->nb_pipes)
		{
			free(pipex->pipefd[i]);
			pipex->pipefd[i] = NULL;
		}
	}
	else
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

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}
