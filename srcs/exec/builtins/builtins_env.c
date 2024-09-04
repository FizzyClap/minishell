/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:52:21 by roespici          #+#    #+#             */
/*   Updated: 2024/09/04 15:39:05 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	sort_and_print(t_env *env, char **args)
{
	t_env	*sorted_env;

	if (!args[1])
	{
		sorted_env = copy_env(env);
		sort_env(sorted_env);
		builtin_env(sorted_env, args[0]);
		free_env(sorted_env);
	}
}

void	builtin_export(t_env *env, char **args)
{
	t_env	*current;
	bool	var_exist;
	int		i;

	i = 0;
	while (args[++i])
	{
		var_exist = false;
		current = env;
		while (current)
		{
			if (ft_strncmp(current->var, args[i], \
				ft_strchr(args[i], '=') - args[i]) == 0)
			{
				var_exist = true;
				if (ft_strchr(args[i], '='))
					modify_node(current, args[i]);
				break ;
			}
			if (!current->next && var_exist == false)
				add_node(&current, args[i]);
			current = current->next;
		}
	}
	sort_and_print(env, args);
}

void	builtin_unset(t_env *env, char **args)
{
	t_env	*current;
	t_env	*temp;
	int		i;

	i = 0;
	while (args[++i])
	{
		current = env;
		while (current && current->next)
		{
			if (ft_strcmp(current->next->var, args[i]) == 0)
			{
				temp = current->next;
				current->next = current->next->next;
				free(temp->var);
				free(temp->args);
				free(temp);
			}
			else
				current = current->next;
		}
		current = current->next;
	}
}

void	builtin_env(t_env *head, char *command)
{
	t_env	*current;

	current = head;
	while (current)
	{
		if (current->token)
		{
			if (current->args[0] != '"')
				printf("%s=\"%s\"\n", current->var, current->args);
			else
				printf("%s=%s\n", current->var, current->args);
		}
		else if (ft_strcmp((command), "export") == 0)
			printf("%s\n", current->var);
		current = current->next;
	}
}
