/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:05:45 by roespici          #+#    #+#             */
/*   Updated: 2024/09/17 15:01:52 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_env(t_env **env, char *const *envp)
{
	int	i;

	if (!envp[0])
	{
		ft_putstr_fd("Fraudistan: environment is missing\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (envp[++i])
		add_node(env, envp[i]);
}

void	init_pipex(t_pipex *pipex, t_cmd *command, t_env *env)
{
	t_cmd	*size;
	int		i;

	pipex->env = env;
	pipex->cmd = command;
	pipex->i = -1;
	pipex->infile_error = NULL;
	pipex->outfile_error = NULL;
	pipex->limiter = NULL;
	size = pipex->cmd;
	pipex->nb_pipes = list_cmd_size(size) - 1;
	pipex->status = 1;
	pipex->pipefd = malloc(sizeof(int *) * pipex->nb_pipes);
	if (!pipex->pipefd)
		return ;
	i = -1;
	while (++i < pipex->nb_pipes)
		pipex->pipefd[i] = ft_calloc(sizeof(int), 2);
	pipex->child = ft_calloc(sizeof(pid_t), (pipex->nb_pipes + 1));
	if (!pipex->child)
		return ;
}
