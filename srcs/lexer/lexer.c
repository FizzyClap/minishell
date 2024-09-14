/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoy <ggoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:33:13 by roespici          #+#    #+#             */
/*   Updated: 2024/09/14 16:24:17 by ggoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_token(char *element)
{
	if (ft_strcmp(element, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(element, "<") == 0)
		return (IN);
	else if (ft_strcmp(element, ">") == 0)
		return (OUT);
	else if (ft_strcmp(element, "<<") == 0)
		return (HEREDOC);
	else if (ft_strcmp(element, ">>") == 0)
		return (APPEND);
	else if (ft_strcmp(element, "||") == 0)
		return (OR);
	else if (ft_strcmp(element, "&&") == 0)
		return (AND);
	else
		return (WORD);
}

static int	lexer_len(char *input, int start)
{
	bool	quote;
	bool	d_quote;
	int		i;

	quote = false;
	d_quote = false;
	i = 0;
	start--;
	while (input[++start])
	{
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

static int	lexer_progress(char *input, int start)
{
	bool	quote;
	bool	d_quote;

	quote = false;
	d_quote = false;
	start--;
	while (input[++start])
	{
		if (input[start] == ' ' && quote == false && d_quote == false)
			return (start);
		if (input[start] == '\"' && quote == false)
			d_quote = ft_change_bool(d_quote);
		else if (input[start] == '\'' && d_quote == false)
			quote = ft_change_bool(quote);
	}
	return (start);
}

static t_lexer	*lexer_dup(char *input, int start)
{
	bool	quote;
	bool	d_quote;
	t_lexer	*new;
	int		len;
	int		i;

	i = 0;
	new = lexer_new(NULL, 0);
	quote = false;
	d_quote = false;
	len = lexer_len(input, start);
	new->element = ft_calloc(len + 1, sizeof(char));
	start--;
	while (input[++start] && i < len)
	{
		if (input[start] && input[start] == '\"' && quote == false)
			d_quote = change_bool(d_quote, new);
		else if (input[start] && input[start] == '\'' && d_quote == false)
			quote = change_bool(quote, new);
		else
			new->element[i++] = input[start];
	}
	return (new);
}

t_lexer	*make_lexer(char *input)
{
	t_lexer	*lexer;
	t_lexer	*new;
	int		start;

	start = 0;
	lexer = NULL;
	while (input[start])
	{
		while (input[start] == ' ')
			start++;
		if (input[start] && input[start] != ' ')
		{
			new = lexer_dup(input, start);
			new->token = change_token(new);
			lexer_add_back(&lexer, new);
			start = lexer_progress(input, start);
		}
	}
	if (check_valid_lex(lexer) == 0)
	{
		free_lexer(lexer);
		return (NULL);
	}
	return (lexer);
}
