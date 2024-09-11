/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoy <ggoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:34:23 by roespici          #+#    #+#             */
/*   Updated: 2024/09/09 10:36:15 by ggoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer	*clean_redir(t_lexer *lexer)
{
	t_lexer	*clean;
	char	*itoa;

	clean = NULL;
	while (lexer)
	{
		itoa = ft_itoa(lexer->token);
		if (ft_chrinstr("2345", itoa[0]) == 0)
		{
			// if !lexer->next->next = FIN DU MONDE
			lexer_add_back(&clean, lexer_new(ft_strdup(lexer->next->element), lexer->token));
			lexer = lexer->next->next;
		}
		else
		{
			lexer_add_back(&clean, lexer_new(ft_strdup(lexer->element), lexer->token));
			lexer = lexer->next;
		}
		free(itoa);
	}
	return (clean);
}
