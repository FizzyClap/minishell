/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:25:36 by roespici          #+#    #+#             */
/*   Updated: 2024/09/14 12:50:56 by roespici         ###   ########.fr       */
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

void	execute_builtins(t_env *env, t_cmd *command, int fd)
{
	if (ft_strcmp(command->cmd, "echo") == 0)
		builtin_echo(command, fd);
	else if (ft_strcmp(command->cmd, "cd") == 0)
		builtin_cd(env, command->args, fd);
	else if (ft_strcmp(command->cmd, "pwd") == 0)
		builtin_pwd(env, command->args, fd);
	else if (ft_strcmp(command->cmd, "export") == 0)
		builtin_export(env, command, fd);
	else if (ft_strcmp(command->cmd, "unset") == 0)
		builtin_unset(env, command->args);
	else if (ft_strcmp(command->cmd, "env") == 0)
		builtin_env(env, command->cmd, fd);
	else if (ft_strcmp(command->cmd, "exit") == 0)
		builtin_exit(env, command);
	else
		printf("%s: command not found\n", command->cmd);
}

t_env	*copy_env(t_env *env)
{
	t_env	*copy;
	t_env	*temp;

	copy = NULL;
	temp = env;
	while (temp)
	{
		add_node(&copy, temp->line);
		temp = temp->next;
	}
	return (copy);
}

void	free_env(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->line);
		free(head->var);
		free(head->args);
		free(head);
		head = tmp;
	}
}

char	*get_env(t_env *env, char *var_name)
{
	while (env)
	{
		if (ft_strcmp(env->var, var_name) == 0)
			return (env->args);
		env = env->next;
	}
	return (NULL);
}
