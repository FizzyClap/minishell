/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartan <gartan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:11:14 by roespici          #+#    #+#             */
/*   Updated: 2024/09/09 13:04:11 by gartan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtins(t_cmd *command)
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
	if (args)
	{
		while (args[++i])
			free(args[i]);
		free(args);
	}
}
