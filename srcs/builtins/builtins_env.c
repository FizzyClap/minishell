/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoy <ggoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:52:21 by roespici          #+#    #+#             */
/*   Updated: 2024/09/13 09:58:19 by ggoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	sort_and_print(t_env *env, t_cmd *cmd, int fd)
{
	t_env	*sorted_env;
	int		nb_args;

	nb_args = ft_count_args(cmd->args);
	if (ft_strcmp(cmd->cmd, "export") == 0 && nb_args == 1)
	{
		sorted_env = copy_env(env);
		sort_env(sorted_env);
		builtin_env(sorted_env, cmd->cmd, fd);
		free_env(sorted_env);
	}
}

void	builtin_export(t_env *env, t_cmd *cmd, int fd)
{
	t_env	*current;
	bool	var_exist;
	int		i;

	i = 0;
	while (cmd->args[++i])
	{
		var_exist = false;
		current = env;
		while (current)
		{
			if (ft_strncmp(current->var, cmd->args[i], \
				ft_strchr(cmd->args[i], '=') - cmd->args[i]) == 0)
			{
				var_exist = true;
				if (ft_strchr(cmd->args[i], '='))
					modify_node(current, cmd->args[i]);
				break ;
			}
			if (!current->next && var_exist == false)
				add_node(&current, cmd->args[i]);
			current = current->next;
		}
	}
	sort_and_print(env, cmd, fd);
}

void	builtin_unset(t_env *env, char **args)
{
	t_env	*current;
	t_env	*prev;
	t_env	*temp;
	int		i;

	i = 0;
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

void	builtin_env(t_env *head, char *command, int fd)
{
	t_env	*current;

	current = head;
	while (current)
	{
		if (ft_strcmp(command, "export") == 0)
			ft_putstr_fd("declare -x ", fd);
		if (current->token)
			ft_fprintf(fd, "%s=\"%s\"\n", current->var, current->args);
		else if (ft_strcmp(command, "export") == 0)
			ft_fprintf(fd, "%s\n", current->var);
		current = current->next;
	}
}

void	set_env(t_env *env, char *var_name, char *new_path)
{
	while (env)
	{
		if (ft_strcmp(env->var, var_name) == 0)
		{
			free(env->args);
			env->args = ft_strdup(new_path);
			return ;
		}
		env = env->next;
	}
}
