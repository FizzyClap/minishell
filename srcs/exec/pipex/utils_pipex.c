/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 08:29:58 by roespici          #+#    #+#             */
/*   Updated: 2024/09/02 09:10:20 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	error_exit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int	open_infile(t_pipex *pipex, char **argv)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (access(argv[1], F_OK) == FAILURE)
	{
		pipex->infile_open = 0;
		pipex->nb_pipes--;
		ft_printf("zsh: no such file or directory: %s\n", argv[1]);
		return (FAILURE);
	}
	if (access(argv[1], R_OK) == FAILURE)
	{
		pipex->infile_open = 0;
		pipex->nb_pipes--;
		ft_printf("zsh: permission denied: %s\n", argv[1]);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	open_outfile(t_pipex *pipex, int argc, char **argv)
{
	int	last_arg;

	last_arg = argc - 1;
	if (!pipex->limiter)
		pipex->outfile = open(argv[last_arg], O_WRONLY | O_CREAT | O_TRUNC, \
		0644);
	else
		pipex->outfile = open(argv[last_arg], O_WRONLY | O_CREAT | O_APPEND, \
		0644);
	if (access(argv[last_arg], W_OK) == FAILURE)
	{
		pipex->outfile_open = 0;
		if (pipex->infile_open)
			pipex->nb_pipes--;
		if (pipex->limiter)
			return (FAILURE);
		ft_printf("zsh: permission denied: %s\n", argv[last_arg]);
		return (FAILURE);
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

void	init_pipex(t_pipex *pipex, int argc, char **argv, char *const *envp)
{
	int	i;

	pipex->i = -1;
	if (ft_strcmp(argv[1], "here_doc") == 0)
		pipex->nb_pipes = argc - 5;
	else
		pipex->nb_pipes = argc - 4;
	pipex->envp = envp;
	pipex->pipefd = malloc(sizeof(int *) * (pipex->nb_pipes));
	if (!pipex->pipefd)
		return ;
	i = -1;
	while (++i < pipex->nb_pipes)
		pipex->pipefd[i] = ft_calloc(sizeof(int), 2);
	pipex->child = malloc(sizeof(pid_t) * (pipex->nb_pipes + 1));
	if (!pipex->child)
		return ;
	pipex->infile_open = 1;
	pipex->outfile_open = 1;
	pipex->limiter = NULL;
	pipex->status = 1;
	pipex->exit_status = 0;
}
