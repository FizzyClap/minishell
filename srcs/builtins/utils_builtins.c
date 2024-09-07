/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:11:14 by roespici          #+#    #+#             */
/*   Updated: 2024/09/07 10:40:44 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtins(t_cmd *command)
{
	if ((ft_strncmp(command->cmd, "cd", ft_strlen("cd")) == 0))
		return (ISBUILTINS);
	if ((ft_strncmp(command->cmd, "echo", ft_strlen("echo")) == 0))
		return (ISBUILTINS);
	if ((ft_strcmp(command->cmd, "pwd") == 0))
		return (ISBUILTINS);
	if ((ft_strncmp(command->cmd, "export", ft_strlen("export")) == 0))
		return (ISBUILTINS);
	if ((ft_strncmp(command->cmd, "unset", ft_strlen("unset")) == 0))
		return (ISBUILTINS);
	if ((ft_strcmp(command->cmd, "env") == 0))
		return (ISBUILTINS);
	if ((ft_strncmp(command->cmd, "exit", ft_strlen("exit")) == 0))
		return (ISBUILTINS);
	return (ISNOTBUILTINS);
}

void	sort_env(t_env *env)
{
	t_env	*current_node;
	t_env	*next_node;
	t_env	*min_node;

	current_node = env;
	while (current_node)
	{
		min_node = current_node;
		next_node = current_node->next;
		while (next_node)
		{
			if (ft_strcmp(next_node->var, min_node->var) < 0)
				min_node = next_node;
			next_node = next_node->next;
		}
		if (min_node != current_node)
			swap_nodes(current_node, min_node);
		current_node = current_node->next;
	}
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
	t_env	*temp;

	while (head)
	{
		temp = head->next;
		free(head->line);
		free(head->var);
		free(head->args);
		free(head);
		head = temp;
	}
}

void	free_split(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		free(args[i]);
	free(args);
}