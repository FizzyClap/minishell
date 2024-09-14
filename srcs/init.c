/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:40:31 by roespici          #+#    #+#             */
/*   Updated: 2024/09/14 09:51:01 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_env(t_env **env)
{
	int	i;

	i = -1;
	while (__environ[++i])
		add_node(env, __environ[i]);
}

void	init_pipex(t_pipex *pipex, t_cmd *command, t_env *env)
{
	t_cmd	*size;
	int		i;

	pipex->env = env;
	pipex->cmd = command;
	pipex->i = -1;
	pipex->print_msg = false;
	pipex->limiter = NULL;
	size = pipex->cmd;
	pipex->nb_pipes = list_cmd_size(size) - 1;
	i = -1;
	pipex->exit_status = 0;
	pipex->status = 1;
	pipex->pipefd = malloc(sizeof(int *) * pipex->nb_pipes);
	if (!pipex->pipefd)
		return ;
	i = -1;
	while (++i < pipex->nb_pipes)
		pipex->pipefd[i] = ft_calloc(sizeof(int), 2);
	pipex->child = malloc(sizeof(pid_t) * (pipex->nb_pipes + 1));
	if (!pipex->child)
		return ;
}
