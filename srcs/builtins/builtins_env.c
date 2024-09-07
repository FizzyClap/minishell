/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:52:21 by roespici          #+#    #+#             */
/*   Updated: 2024/09/07 13:48:44 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	sort_and_print(t_env *env, char *cmd, char **args)
{
	t_env	*sorted_env;
	int		nb_args;

	nb_args = 0;
	if (args)
		nb_args = ft_count_args(args);
	if (ft_strcmp(cmd, "export") == 0 && nb_args == 0)
	{
		sorted_env = copy_env(env);
		sort_env(sorted_env);
		builtin_env(sorted_env, cmd);
		free_env(sorted_env);
	}
}

void	builtin_export(t_env *env, char *cmd, char **args)
{
	t_env	*current;
	bool	var_exist;
	int		i;

	i = -1;
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
	sort_and_print(env, cmd, args);
}

void	builtin_unset(t_env *env, char **args)
{
	t_env	*current;
	t_env	*prev;
	t_env	*temp;
	int		i;

	i = -1;
	while (args[++i])
	{
		current = env;
		while (current->next)
		{
			if (ft_strcmp(current->next->var, args[i]) == 0)
			{
				prev = current;
				temp = current->next;
				prev->next = current->next->next;
				free(temp->line);
				free(temp->var);
				free(temp->args);
				free(temp);
			}
			else
				current = current->next;
		}
	}
}

void	builtin_env(t_env *head, char *command)
{
	t_env	*current;

	current = head;
	while (current)
	{
		if (ft_strcmp(command, "export") == 0)
			printf("declare -x ");
		if (current->token)
		{
			if (current->args[0] != '"')
				printf("%s=\"%s\"\n", current->var, current->args);
			else
				printf("%s=%s\n", current->var, current->args);
		}
		else if (ft_strcmp(command, "export") == 0)
			printf("%s\n", current->var);
		current = current->next;
	}
}
