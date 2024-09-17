/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:04:01 by roespici          #+#    #+#             */
/*   Updated: 2024/09/17 14:45:58 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer	*lexer_new(char *element, int token, int index)
{
	t_lexer	*tlex;

	tlex = malloc(sizeof(t_lexer));
	tlex->element = element;
	tlex->token = token;
	tlex->index = index;
	tlex->next = NULL;
	return (tlex);
}

static t_lexer	*lexer_last(t_lexer *lst)
{
	if (!lst)
		return (NULL);
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	lexer_add_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*last_element;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last_element = lexer_last(*lst);
	last_element->next = new;
}
