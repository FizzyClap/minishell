/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:40:31 by roespici          #+#    #+#             */
/*   Updated: 2024/09/06 09:11:46 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_env(t_env **env)
{
	int	i;

	i = -1;
	while (__environ[++i])
		add_node(env, __environ[i]);
}

static void	init_cmd(t_cmd *command)
{
	command->line = NULL;
	command->args = NULL;
	command->exit_code = 1;
	command->output_redirection = NULL;
	command->next = NULL;
}

void	init_pipex(t_pipex *pipex, t_cmd *command, t_env *env)
{
	int	i;

	pipex->i = -1;
	pipex->env = env;
	pipex->infile_exist = 1;
	pipex->infile_open = 1;
	pipex->outfile_open = 1;
	pipex->limiter = NULL;
	pipex->nb_pipes = 0;
	i = -1;
	while (command->args[++i])
		if (ft_strcmp(command->args[i], "|") == 0)
			pipex->nb_pipes++;
	pipex->pipefd = malloc(sizeof(int *) * pipex->nb_pipes);
	pipex->status = 1;
	pipex->exit_status = 0;
	if (!pipex->pipefd)
		return ;
	i = -1;
	while (++i < pipex->nb_pipes)
		pipex->pipefd[i] = ft_calloc(sizeof(int), 2);
	pipex->child = malloc(sizeof(pid_t) * (pipex->nb_pipes + 1));
	if (!pipex->child)
		return ;
}

void	init_minishell(t_env **env, t_cmd *command)
{
	init_env(env);
	init_cmd(command);
}
