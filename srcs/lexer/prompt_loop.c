/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:27:10 by roespici          #+#    #+#             */
/*   Updated: 2024/09/17 14:47:16 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	quote_check(char *str);
static int	check_valid_lex(t_lexer *lexer);

t_cmd	*prompt_loop(char *line)
{
	t_lexer		*lexer;
	t_lexer		*lex_redir;
	t_split_cmd	*split;
	t_cmd		*final;

	final = NULL;
	if (quote_check(line) == 0)
		return (NULL);
	lexer = make_lexer(line);
	if (check_valid_lex(lexer) == 0)
	{
		free_lexer(lexer);
		return (NULL);
	}
	if (lexer == NULL)
		return (NULL);
	lex_redir = clean_redir(lexer);
	if (lex_redir == NULL)
		return (NULL);
	free_lexer(lexer);
	split = split_cmd(lex_redir);
	free_lexer(lex_redir);
	final = make_cmd(split);
	free_split_cmd(split);
	return (final);
}

static int	quote_check(char *str)
{
	bool	quote;
	bool	d_quote;
	int		i;

	i = -1;
	quote = false;
	d_quote = false;
	while (str[++i])
	{
		if (str[i] && str[i] == '\"' && quote == false)
			d_quote = ft_change_bool(d_quote);
		else if (str[i] && str[i] == '\'' && d_quote == false)
			quote = ft_change_bool(quote);
	}
	if (quote == true || d_quote == true)
	{
		ft_fprintf(STDERR_FILENO, "Fraudistan: quotes unclosed\n");
		return (0);
	}
	else
		return (1);
}

static int	check_valid_lex(t_lexer *lexer)
{
	t_lexer	*tmp;

	tmp = lexer;
	while (tmp)
	{
		if (tmp->next && tmp->token == PIPE && tmp->next->token == PIPE)
		{
			ft_fprintf(2, "%s `%s'\n", ERR_SYNT, tmp->next->element);
			return (0);
		}
		else if (tmp->next && tmp->token > PIPE && tmp->next->token > PIPE)
		{
			ft_fprintf(2, "%s `%s'\n", ERR_SYNT, tmp->next->element);
			return (0);
		}
		else if (!tmp->next && tmp->token > PIPE && tmp->token < 7)
		{
			ft_fprintf(STDERR_FILENO, "%s%s", ERR_SYNT, " `newline'\n");
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
