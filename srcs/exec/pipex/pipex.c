/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:39:52 by roespici          #+#    #+#             */
/*   Updated: 2024/09/04 09:08:41 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static pid_t	fork_child(void)
{
	pid_t	child;

	child = fork();
	if (child == FAILURE)
		error_exit("Fork error");
	return (child);
}

static void	exec_command(t_pipex *pipex, char *command)
{
	char	*path;
	char	**args;

	args = ft_split(command, ' ');
	path = get_path(pipex, args[0]);
	if (!path)
	{
		free_split(args);
		free_pipex(pipex);
		error_exit("Command not found in path");
	}
	free(args[0]);
	args[0] = path;
	if (execve(args[0], args, pipex->envp) == FAILURE)
	{
		free_split(args);
		free_pipex(pipex);
		error_exit("Error executing command");
	}
}

static void	exec(t_pipex *pipex, int inputfd, int outputfd, char *cmd)
{
	if (dup2(inputfd, STDIN_FILENO) == FAILURE)
		error_exit("Dup2 input error");
	if (dup2(outputfd, STDOUT_FILENO) == FAILURE)
		error_exit("Dup2 output error");
	close(inputfd);
	close(outputfd);
	exec_command(pipex, cmd);
	error_exit("Execve error");
}

static void	chose_pipe(t_pipex *pipex, int i, int start, char **argv)
{
	if (i == 0)
	{
		if (pipex->nb_pipes > 0)
			close(pipex->pipefd[i][0]);
		if (pipex->infile_open)
			exec(pipex, pipex->infile, pipex->pipefd[i][1], argv[start]);
		else
		{
			if (pipex->nb_pipes == 0)
				exec(pipex, STDIN_FILENO, pipex->outfile, argv[start]);
			else
				exec(pipex, STDIN_FILENO, pipex->pipefd[i][1], argv[start]);
		}
	}
	else if (i == pipex->nb_pipes)
	{
		close(pipex->pipefd[i - 1][1]);
		exec(pipex, pipex->pipefd[i - 1][0], pipex->outfile, argv[start + i]);
	}
	else
	{
		close(pipex->pipefd[i][0]);
		exec(pipex, pipex->pipefd[i - 1][0], pipex->pipefd[i][1], \
			argv[start + i]);
	}
}

void	execute_pipes(t_pipex *pipex, char **argv, int start)
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
		{
			if (ft_strcmp(argv[1], "here_doc") == 0)
				chose_pipe(pipex, i, 3, argv);
			else
				chose_pipe(pipex, i, start, argv);
		}
		else
		{
			if (i > 0)
				close(pipex->pipefd[i - 1][0]);
			if (i < pipex->nb_pipes)
				close(pipex->pipefd[i][1]);
		}
	}
}
