/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoy <ggoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:42:23 by roespici          #+#    #+#             */
/*   Updated: 2024/09/09 10:37:06 by ggoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_split_cmd	*split_new(void)
{
	t_split_cmd	*split;

	split = malloc(sizeof(t_split_cmd));
	split->cmd = NULL;
	split->next = NULL;
	return (split);
}

static t_split_cmd	*split_last(t_split_cmd *lst)
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

static void	split_add_back(t_split_cmd **lst, t_split_cmd *new)
{
	t_split_cmd	*last_element;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last_element = split_last(*lst);
	last_element->next = new;
}

t_split_cmd	*split_cmd(t_lexer *lexer)
{
	t_split_cmd	*split;
	t_split_cmd	*new;
	t_lexer		*lex;

	split = NULL;
	while (lexer)
	{
		new = split_new();
		while (lexer && lexer->token != PIPE)
		{
			lex = lexer_new(ft_strdup(lexer->element), lexer->token);
			lexer_add_back(&new->cmd, lex);
			lexer = lexer->next;
		}
		if (lexer && lexer->token == PIPE)
			lexer = lexer->next;
		split_add_back(&split, new);
	}
	return (split);
}
