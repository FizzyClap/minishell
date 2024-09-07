/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:34:44 by roespici          #+#    #+#             */
/*   Updated: 2024/09/07 16:41:08 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

pid_t	fork_child(void)
{
	pid_t	child;

	child = fork();
	if (child == FAILURE)
		error_exit("Fork error");
	return (child);
}

static void	chose_pipe(t_pipex *pipex, int i)
{
	if (i == 0)
	{
		if (pipex->nb_pipes > 0)
			close(pipex->pipefd[i][0]);
		if (pipex->infile_open)
			exec(pipex, pipex->infile, pipex->pipefd[i][1]);
		else
		{
			if (pipex->nb_pipes == 0)
				exec(pipex, STDIN_FILENO, pipex->outfile);
			else
				exec(pipex, STDIN_FILENO, pipex->pipefd[i][1]);
		}
	}
	else if (i == pipex->nb_pipes)
	{
		close(pipex->pipefd[i - 1][1]);
		exec(pipex, pipex->pipefd[i - 1][0], pipex->outfile);
	}
	else
	{
		close(pipex->pipefd[i][0]);
		exec(pipex, pipex->pipefd[i - 1][0], pipex->pipefd[i][1]);
	}
}

void	execute_pipes(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i <= pipex->nb_pipes)
	{
		if (i < pipex->nb_pipes)
			if (pipe(pipex->pipefd[i]) == FAILURE)
				error_exit("Pipe error");
		pipex->child[i] = fork_child();
		if (pipex->child[i] == 0)
			chose_pipe(pipex, i);
		else
		{
			if (i > 0)
				close(pipex->pipefd[i - 1][0]);
			if (i < pipex->nb_pipes)
				close(pipex->pipefd[i][1]);
		}
	}
}

void	exec_command(t_pipex *pipex)
{
	char	*path;

	path = get_path(pipex);
	if (!path)
	{
		//FREE;
		error_exit("Command not found in path");
	}
	if (execve(pipex->cmd, pipex->cmd->args, pipex->env->tab_env) == FAILURE)
	{
		//FREE
		error_exit("Error executing command");
	}
}

void	exec(t_pipex *pipex, int inputfd, int outputfd)
{
	if (dup2(inputfd, STDIN_FILENO) == FAILURE)
		error_exit("Dup2 input error");
	if (dup2(outputfd, STDOUT_FILENO) == FAILURE)
		error_exit("Dup2 output error");
	close(inputfd);
	close(outputfd);
	exec_command(pipex);
	error_exit("Execve error");
}
