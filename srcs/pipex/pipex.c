/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:34:44 by roespici          #+#    #+#             */
/*   Updated: 2024/09/09 17:16:42 by roespici         ###   ########.fr       */
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
		exec(pipex, STDIN_FILENO, pipex->outfile);
		//if (pipex->infile_open && i == pipex->nb_pipes && !pipex->outfile_open)
		//	exec(pipex, pipex->infile, STDOUT_FILENO);
		//else if (pipex->infile_open && pipex->outfile_open)
		//	exec(pipex, pipex->infile, pipex->outfile);
		//else if (pipex->infile_open)
		//	exec(pipex, pipex->infile, pipex->pipefd[i][1]);
		//else
		//{
		//	if (pipex->nb_pipes == 0 && pipex->outfile_open)
		//		exec(pipex, STDIN_FILENO, pipex->outfile);
		//	else if (pipex->nb_pipes == 0)
		//		exec(pipex, STDIN_FILENO, STDOUT_FILENO);
		//	else
		//		exec(pipex, STDIN_FILENO, pipex->pipefd[i][1]);
		//}
	}
	else if (i == pipex->nb_pipes)
	{
		close(pipex->pipefd[i - 1][1]);
		if (pipex->outfile_open)
			exec(pipex, pipex->pipefd[i - 1][0], pipex->outfile);
		else
			exec(pipex, pipex->pipefd[i - 1][0], STDOUT_FILENO);
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
		{
			if (pipe(pipex->pipefd[i]) == FAILURE)
				error_exit("Pipe error");
		}
		if (is_builtins(pipex->cmd))
			execute_builtins(pipex->env, pipex->cmd);
		else
		{
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
}

void	exec_command(t_pipex *pipex)
{
	char	*path;

	path = get_path(pipex);
	if (!path)
	{
		free_pipex(pipex);
		printf("bash: command not found: %s\n", pipex->cmd->cmd);
		exit(COMMAND_NOT_FOUND);
	}
	free(pipex->cmd->args[0]);
	pipex->cmd->args[0] = path;
	if (execve(pipex->cmd->args[0], pipex->cmd->args, __environ) == FAILURE)
	{
		free_pipex(pipex);
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
	if (outputfd != STDOUT_FILENO)
		close(outputfd);
	exec_command(pipex);
	error_exit("Execve error");
}

void	execute_pipex (t_cmd *command, t_env *env)
{
	t_pipex *pipex;
	int		i;

	pipex = malloc(sizeof(t_pipex));
	init_pipex(pipex, command, env);
	while (pipex->cmd)
	{
		open_infile(pipex);
		open_outfile(pipex);
		execute_pipes(pipex);
		pipex->cmd = pipex->cmd->next;
	}
	i = -1;
	while (++i <= pipex->nb_pipes)
		waitpid(pipex->child[i], &pipex->status, 0);
}
