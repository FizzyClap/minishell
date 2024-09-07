/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartan <gartan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:34:23 by roespici          #+#    #+#             */
/*   Updated: 2024/09/07 17:51:56 by gartan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer	*clean_redir(t_lexer *lexer)
{
	t_lexer	*clean;
	t_lexer	*new;
	char	*itoa;

	clean = NULL;
	while (lexer)
	{
		itoa = ft_itoa(lexer->token);
		if (ft_chrinstr("2345", itoa[0]) == 0)
		{
			new = lexer_new(lexer->next->element, lexer->token);
			lexer = lexer->next->next;
		}
		else
		{
			new = lexer_new(lexer->element, lexer->token);
			lexer = lexer->next;
		}
		lexer_add_back(&clean, new);
		free(itoa);
	}
	free_lexer(lexer);
	return (clean);
}
