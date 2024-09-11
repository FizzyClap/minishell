/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoy <ggoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:56:05 by roespici          #+#    #+#             */
/*   Updated: 2024/09/11 15:20:50 by ggoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	fill_here_doc(t_pipex *pipex)
{
	char	*line;

	pipex->infile = open("here_doc.tmp", O_CREAT | O_WRONLY, 0644);
	if (pipex->infile < 0)
		error_exit("Here_doc error");
	while (1)
	{
		ft_putstr("> ");
		line = get_next_line(STDIN_FILENO);
		if (ft_strcmp(line, pipex->limiter) == 10)
		{
			free(line);
			break ;
		}
		if (pipex->outfile_open)
			ft_putstr_fd(line, pipex->infile);
		free(line);
	}
	close(pipex->infile);
}

static void	exec_here_doc(t_pipex *pipex)
{
	pipex->infile = open("here_doc.tmp", O_RDONLY);
	if (pipex->cmd->cmd)
		execute_pipes(pipex);
}

static void	close_here_doc(t_pipex *pipex)
{
	close_pipes(pipex);
	unlink("here_doc.tmp");
}

void	here_doc(t_pipex *pipex)
{
	if (pipex->cmd->redir->element)
		pipex->limiter = ft_strdup(pipex->cmd->redir->element);
	open_outfile(pipex);
	fill_here_doc(pipex);
	if (!pipex->outfile_open)
	{
		printf("bash: %s: Permission denied\n", pipex->cmd->redir->element);
		unlink("here_doc.tmp");
		free(pipex->limiter);
		return ;
	}
	exec_here_doc(pipex);
	close_here_doc(pipex);
	free(pipex->limiter);
}
