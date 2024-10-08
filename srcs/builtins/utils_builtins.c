/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:03:39 by roespici          #+#    #+#             */
/*   Updated: 2024/09/24 08:43:27 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtins(t_cmd *command)
{
	if (command->cmd)
	{
		if ((ft_strcmp(command->cmd, "cd") == 0))
			return (ISBUILTINS);
		if ((ft_strcmp(command->cmd, "echo") == 0))
			return (ISBUILTINS);
		if ((ft_strcmp(command->cmd, "pwd") == 0))
			return (ISBUILTINS);
		if ((ft_strcmp(command->cmd, "export") == 0))
			return (ISBUILTINS);
		if ((ft_strcmp(command->cmd, "unset") == 0))
			return (ISBUILTINS);
		if ((ft_strcmp(command->cmd, "env") == 0))
			return (ISBUILTINS);
		if ((ft_strcmp(command->cmd, "exit") == 0))
			return (ISBUILTINS);
	}
	return (ISNOTBUILTINS);
}

void	execute_builtins(t_pipex *pipex)
{
	open_files(pipex);
	if (files_are_valid(pipex, false) == FAILURE)
		return ;
	g_exit_code = 0;
	if (ft_strcmp(pipex->cmd->cmd, "echo") == 0)
		builtin_echo(pipex->cmd, pipex->outfile);
	else if (ft_strcmp(pipex->cmd->cmd, "cd") == 0)
		builtin_cd(pipex->env, pipex->cmd->args, pipex->outfile);
	else if (ft_strcmp(pipex->cmd->cmd, "pwd") == 0)
		builtin_pwd(pipex->env, pipex->outfile);
	else if (ft_strcmp(pipex->cmd->cmd, "export") == 0)
		builtin_export(pipex->env, pipex->cmd, pipex->outfile);
	else if (ft_strcmp(pipex->cmd->cmd, "unset") == 0)
		builtin_unset(pipex->env, pipex->cmd->args);
	else if (ft_strcmp(pipex->cmd->cmd, "env") == 0)
		builtin_env(pipex->env, pipex->cmd, pipex->outfile);
	else if (ft_strcmp(pipex->cmd->cmd, "exit") == 0)
		builtin_exit(pipex->env, pipex->cmd);
}
