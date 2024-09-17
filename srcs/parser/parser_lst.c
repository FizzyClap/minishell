/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:04:27 by roespici          #+#    #+#             */
/*   Updated: 2024/09/17 15:05:56 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_cmd	*cmd_last(t_cmd *lst);

t_cmd	*cmd_new(char *cmd, char **args, t_lexer *out)
{
	t_cmd	*tcmd;

	tcmd = malloc(sizeof(t_cmd));
	tcmd->cmd = cmd;
	tcmd->args = args;
	tcmd->redir = out;
	tcmd->next = NULL;
	return (tcmd);
}

void	cmd_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last_element;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last_element = cmd_last(*lst);
	last_element->next = new;
}

static t_cmd	*cmd_last(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

int	list_cmd_size(t_cmd *lst)
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
