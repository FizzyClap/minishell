/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:34:44 by roespici          #+#    #+#             */
/*   Updated: 2024/09/12 09:05:05 by roespici         ###   ########.fr       */
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
		if (i == pipex->nb_pipes || pipex->outfile != STDOUT_FILENO)
			exec(pipex, pipex->infile, pipex->outfile);
		else
			exec(pipex, pipex->infile, pipex->pipefd[i][1]);
	}
	else if (i == pipex->nb_pipes)
		exec(pipex, pipex->pipefd[i - 1][0], pipex->outfile);
	else
	{
		close(pipex->pipefd[i][0]);
		if (pipex->outfile != STDOUT_FILENO)
			exec(pipex, pipex->pipefd[i - 1][0], pipex->outfile);
		else
			exec(pipex, pipex->pipefd[i - 1][0], pipex->pipefd[i][1]);
	}
}

void	execute_pipes(t_pipex *pipex)
{
	while (++pipex->i <= pipex->nb_pipes)
	{
		if (pipex->cmd && pipex->cmd->next)
		{
			if (pipe(pipex->pipefd[pipex->i]) == FAILURE)
				error_exit("Pipe error");
		}
		if (pipex->nb_pipes == 0 && is_builtins(pipex->cmd))
			execute_builtins(pipex->env, pipex->cmd, pipex->outfile);
		else
			pipex->child[pipex->i] = fork_child();
		if (pipex->child[pipex->i] == 0)
			chose_pipe(pipex, pipex->i);
		else
		{
			if (pipex->i > 0)
				close(pipex->pipefd[pipex->i - 1][0]);
			if (pipex->i < pipex->nb_pipes)
				close(pipex->pipefd[pipex->i][1]);
		}
		if (pipex->cmd && pipex->cmd->next)
		{
			pipex->cmd = pipex->cmd->next;
			if (open_and_exec(pipex) == FAILURE)
				return ;
		}
	}
}

void	exec_command(t_pipex *pipex)
{
	char	*path;

	if (is_builtins(pipex->cmd))
	{
		execute_builtins(pipex->env, pipex->cmd, pipex->outfile);
		exit(EXIT_SUCCESS);
	}
	path = get_path(pipex);
	if (!path)
	{
		ft_fprintf(pipex->outfile, "%s: command not found\n", pipex->cmd->cmd);
		free_pipex(pipex);
		g_exit_code = COMMAND_NOT_FOUND;
		exit(g_exit_code);
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
	if (inputfd != STDIN_FILENO)
		close(inputfd);
	if (outputfd != STDOUT_FILENO)
		close(outputfd);
	exec_command(pipex);
	error_exit("Execve error");
}

int	open_and_exec(t_pipex *pipex)
{
	if (open_infile(pipex) == FAILURE || open_outfile(pipex) == FAILURE)
		return (FAILURE);
	execute_pipes(pipex);
	return (SUCCESS);
}

void	execute_pipex (t_cmd *command, t_env *env)
{
	t_pipex *pipex;
	int		i;

	pipex = malloc(sizeof(t_pipex));
	init_pipex(pipex, command, env);
	while (open_and_exec(pipex) == FAILURE && pipex->nb_pipes > 0)
	{
		--pipex->nb_pipes;
		pipex->cmd = pipex->cmd->next;
	}
	i = -1;
	while (++i <= pipex->nb_pipes)
		waitpid(pipex->child[i], &pipex->status, 0);
	//free_pipex(pipex);
}
