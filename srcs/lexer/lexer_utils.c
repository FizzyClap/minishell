/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:04:09 by roespici          #+#    #+#             */
/*   Updated: 2024/09/24 08:43:51 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	change_bool(bool quote, t_lexer *new)
{
	new->token += 1;
	if (quote == true)
		quote = false;
	else
		quote = true;
	return (quote);
}

int	check_valid_token(char c, int i)
{
	if ((i > 1 && c == '|'))
	{
		ft_fprintf(STDERR_FILENO, \
			"syntax error near unexpected token `%c'\n", c);
		return (-1);
	}
	else if (i > 2)
	{
		ft_fprintf(STDERR_FILENO, \
			"syntax error near unexpected token `%c'\n", c);
		return (-1);
	}
	else
		return (0);
}

int	next_token_pr(char *input, int start)
{
	char	c;
	int		i;

	i = 0;
	c = input[start];
	if (start > 0 && ft_chrinstr("<>", c) == 0 && \
		ft_chrinstr("\"\'", input[start -1]) == 0)
	{
		while (input[start] && input[start] == c)
			start++;
		return (start);
	}
	else
	{
		while (input[start] && input[start] == c)
		{
			start++;
			i++;
		}
		if (check_valid_token(c, i) == -1)
			return (-1);
		return (start);
	}
}

int	lexer_len(char *input, int start)
{
	bool	quote;
	bool	d_quote;
	int		i;

	quote = false;
	d_quote = false;
	i = 0;
	if (is_token(input[start]) == 1)
		return (next_token(input, start, i));
	start--;
	while (input[++start])
	{
		if (is_token(input[start]) == 1 && quote == false && d_quote == false)
			return (i);
		if (input[start] == ' ' && quote == false && d_quote == false)
			return (i);
		if (input[start] == '\"' && quote == false)
			d_quote = ft_change_bool(d_quote);
		else if (input[start] == '\'' && d_quote == false)
			quote = ft_change_bool(quote);
		else
			i++;
	}
	return (i);
}

int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (SUCCESS);
	else
		return (FAILURE);
}
