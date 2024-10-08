/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:04:05 by roespici          #+#    #+#             */
/*   Updated: 2024/09/17 15:04:51 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	long_line(t_lexer *clean, char *itoa);

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
				return (long_line(clean, itoa), NULL);
			lexer_add_back(&clean, \
				lexer_new(ft_strdup(lexer->next->element), lexer->token, 0));
			lexer = lexer->next->next;
		}
		else
		{
			lexer_add_back(&clean, \
				lexer_new(ft_strdup(lexer->element), lexer->token, 0));
			lexer = lexer->next;
		}
		free(itoa);
	}
	return (clean);
}

static void	long_line(t_lexer *clean, char *itoa)
{
	ft_fprintf(STDERR_FILENO, "syntax error near unexpected token `newline'\n");
	free_lexer(clean);
	free(itoa);
}

int	is_token(char c)
{
	if (ft_chrinstr("|<>", c) == 0)
		return (1);
	else
		return (0);
}

int	next_token(char *input, int start, int i)
{
	char	c;

	i = 0;
	c = input[start];
	while (input[start] && input[start] == c)
	{
		i++;
		start++;
	}
	return (i);
}
