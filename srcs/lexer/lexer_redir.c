/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:34:23 by roespici          #+#    #+#             */
/*   Updated: 2024/09/06 09:17:00 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer	*clean_redir(t_lexer *lexer)
{
	t_lexer	*clean;
	t_lexer	*new;

	clean = NULL;
	while (lexer)
	{
		if (ft_chrinstr("235", ft_itoa(lexer->token)[0]) == 0)
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
	}
	return (clean);
}
