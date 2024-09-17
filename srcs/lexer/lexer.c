#include "../../includes/minishell.h"

static int	check_valid_token(char c, int i)
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

static int	next_token_pr(char *input, int start)
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

static int	lexer_len(char *input, int start)
{
	bool	quote;
	bool	d_quote;
	int		i;

	quote = false;
	d_quote = false;
	i = 0;
	if (is_token(input[start]) == 1)
		return (next_token(input, start, i));
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

static int	lexer_progress(char *input, int start, t_lexer *new)
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
		while (input[start] && input[start] != ' ')
		while (input[start] && input[start] != ' ')
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
