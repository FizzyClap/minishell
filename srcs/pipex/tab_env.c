/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:05:05 by roespici          #+#    #+#             */
/*   Updated: 2024/09/17 14:08:38 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	env_size(t_env *env);

void	create_tab_env(t_env *env)
{
	t_env	*current;
	int		i;

	env->tab_env = malloc(sizeof(char *) * (env_size(env) + 1));
	if (!env->tab_env)
		return ;
	current = env;
	i = 0;
	while (current)
	{
		env->tab_env[i] = ft_strdup(current->line);
		if (!env->tab_env[i])
			return ;
		i++;
		current = current->next;
	}
	env->tab_env[i] = NULL;
}

static int	env_size(t_env *env)
{
	int		size;
	t_env	*current;

	size = 0;
	current = env;
	if (!current)
		return (size);
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}
