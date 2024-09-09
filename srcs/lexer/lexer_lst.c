/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:34:04 by roespici          #+#    #+#             */
/*   Updated: 2024/09/06 09:06:03 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer	*lexer_new(char *element, int token)
{
	t_lexer	*tlex;

	tlex = malloc(sizeof(t_lexer));
	tlex->element = element;
	tlex->token = token;
	tlex->next = NULL;
	return (tlex);
}

static t_lexer	*lexer_last(t_lexer *lst)
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

int	lexer_size(t_lexer *lst)
{
	size_t	count;

	if (!lst)
		return (0);
	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
