/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartan <gartan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:33:13 by roespici          #+#    #+#             */
/*   Updated: 2024/09/07 17:52:27 by gartan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_token(char *element)
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
	//else if (ft_strcmp(element, "$") == 0)
	//	return (DOLLAR);
	else if (ft_strcmp(element, "?") == 0)
		return (QUESTION);
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

static char	*lexer_dup(char *input, int start)
{
	bool	quote;
	bool	d_quote;
	char	*line;
	int		len;
	int		i;

	i = 0;
	quote = false;
	d_quote = false;
	len = lexer_len(input, start);
	line = ft_calloc(len + 1, sizeof(char));
	start--;
	while (input[++start] && i < len)
	{
		if (input[start] && input[start] == '\"' && quote == false)
			d_quote = ft_change_bool(d_quote);
		else if (input[start] && input[start] == '\'' && d_quote == false)
			quote = ft_change_bool(quote);
		else
		{
			line[i] = input[start];
			i++;
		}
	}
	return (line);
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
		new = lexer_new(NULL, 0);
		while (input[start] == ' ')
			start++;
		if (input[start] != ' ')
		{
			new->element = lexer_dup(input, start);
			new->token = find_token(new->element);
			lexer_add_back(&lexer, new);
			start = lexer_progress(input, start);
		}
		free_lexer(new);
		new = NULL;
	}
	return (lexer);
}
