/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:05:39 by roespici          #+#    #+#             */
/*   Updated: 2024/09/17 15:11:12 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_var	*var_last(t_var *lst);

t_var	*var_new(char *variable, bool exist)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!variable)
		var->variable = ft_strdup("");
	else
		var->variable = ft_strdup(variable);
	if (!var->variable)
		return (free(var), NULL);
	var->exist = exist;
	var->next = NULL;
	return (var);
}

void	var_add_back(t_var **lst, t_var *new)
{
	t_var	*last_variable;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last_variable = var_last(*lst);
	last_variable->next = new;
}

static t_var	*var_last(t_var *lst)
{
	if (!lst)
		return (NULL);
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

int	list_var_size(t_cmd *lst)
{
	int	count;

	count = 0;
	if (!lst)
		return (count);
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
