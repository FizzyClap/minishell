/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:04:14 by roespici          #+#    #+#             */
/*   Updated: 2024/09/18 11:51:18 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_lexer	*lexer_dup(char *input, int start);
static int		change_token(t_lexer *new);
static int		find_token(char *element);
static int		lexer_progress(char *input, int start);

t_lexer	*make_lexer(char *input)
{
	t_lexer	*lexer;
	t_lexer	*new;
	int		start;

	start = 0;
	lexer = NULL;
	while (input[start])
	{
		while (is_space(input[start]) == SUCCESS)
			start++;
		while (input[start] && is_space(input[start]) == FAILURE)
		{
			new = lexer_dup(input, start);
			new->token = change_token(new);
			lexer_add_back(&lexer, new);
			start = lexer_progress(input, start);
			if (start == -1)
			{
				free_lexer(lexer);
				return (NULL);
			}
		}
	}
	return (lexer);
}

static t_lexer	*lexer_dup(char *input, int start)
{
	bool	quote;
	bool	d_quote;
	t_lexer	*new;
	int		len;
	int		i;

	i = 0;
	new = lexer_new(NULL, 0, 0);
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

static int	change_token(t_lexer *new)
{
	if ((new->token % 2) != 0)
		return (WORD);
	else
		return (find_token(new->element));
}

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
	else
		return (WORD);
}

static int	lexer_progress(char *input, int start)
{
	bool	quote;
	bool	d_quote;

	quote = false;
	d_quote = false;
	if (is_token(input[start]) == 1)
	{
		start = next_token_pr(input, start);
		return (start);
	}
	start--;
	while (input[++start])
	{
		if (is_token(input[start]) == 1 && quote == false && d_quote == false)
			return (start);
		if (is_space(input[start]) == SUCCESS && quote == false && \
			d_quote == false)
			return (start);
		if (input[start] == '\"' && quote == false)
			d_quote = ft_change_bool(d_quote);
		else if (input[start] == '\'' && d_quote == false)
			quote = ft_change_bool(quote);
	}
	return (start);
}
