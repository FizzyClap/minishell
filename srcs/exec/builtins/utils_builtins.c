/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:11:14 by roespici          #+#    #+#             */
/*   Updated: 2024/09/04 15:32:22 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_builtins(char *command)
{
	if ((ft_strncmp(command, "cd", ft_strlen("cd")) == 0))
		return (ISBUILTINS);
	if ((ft_strncmp(command, "echo", ft_strlen("echo")) == 0))
		return (ISBUILTINS);
	if ((ft_strcmp(command, "pwd") == 0))
		return (ISBUILTINS);
	if ((ft_strncmp(command, "export", ft_strlen("export")) == 0))
		return (ISBUILTINS);
	if ((ft_strncmp(command, "unset", ft_strlen("unset")) == 0))
		return (ISBUILTINS);
	if ((ft_strcmp(command, "env") == 0))
		return (ISBUILTINS);
	if ((ft_strncmp(command, "exit", ft_strlen("exit")) == 0))
		return (ISBUILTINS);
	return (ISNOTBUILTINS);
}

void	init_env(t_env **env)
{
	int	i;

	i = -1;
	while (__environ[++i])
		add_node(env, __environ[i]);
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
	t_env	*new_node;

	copy = NULL;
	temp = env;
	while (temp)
	{
		new_node = create_node(temp->line);
		if (!new_node)
			return (free_env(copy), NULL);
		add_node(&copy, new_node->line);
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
