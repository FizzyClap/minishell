/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:03:43 by roespici          #+#    #+#             */
/*   Updated: 2024/09/17 14:03:44 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
