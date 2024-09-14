/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoy <ggoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:25:36 by roespici          #+#    #+#             */
/*   Updated: 2024/09/14 11:50:28 by ggoy             ###   ########.fr       */
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
