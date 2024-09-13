/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoy <ggoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:10:37 by ggoy              #+#    #+#             */
/*   Updated: 2024/09/13 10:04:34 by ggoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_var	*var_new(char *variable, bool exist)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	var->variable = variable;
	var->exist = exist;
	var->next = NULL;
	return (var);
}

static t_var	*var_last(t_var *lst)
{
	if (!lst)
		return (NULL);
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
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
