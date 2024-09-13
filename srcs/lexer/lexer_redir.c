/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoy <ggoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:34:23 by roespici          #+#    #+#             */
/*   Updated: 2024/09/13 10:57:13 by ggoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_lexer	*long_line(t_lexer *lexer)
{
	t_lexer	*lex;

	lex = lexer;
	lex = lexer_new(lex->next->element, lex->token);
	return (lex);
}

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
			if (!lexer->next)
			{
				printf("syntax error near unexpected token `newline'\n");
				return (free_lexer(clean), free(itoa), NULL);
			}
			lexer_add_back(&clean, long_line(lexer));
			lexer = lexer->next->next;
		}
		else
		{
			lexer_add_back(&clean, long_line(lexer));
			lexer = lexer->next;
		}
		free(itoa);
	}
	return (clean);
}

int	check_valid_lex(t_lexer *lexer)
{
	t_lexer	*tmp;

	tmp = lexer;
	while (tmp)
	{
		if (tmp->next && tmp->token == PIPE && tmp->next->token == PIPE)
		{
			printf("%s `%s'\n", ERR_SYNT, tmp->next->element);
			return (0);
		}
		else if (tmp->next && tmp->token > PIPE && tmp->next->token > WORD)
		{
			printf("%s `%s'\n", ERR_SYNT, tmp->next->element);
			return (0);
		}
		else if (!tmp->next && tmp->token > PIPE && tmp->token < 7)
		{
			printf("%s%s", ERR_SYNT, " `newline'\n");
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
