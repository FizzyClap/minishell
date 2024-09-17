#include "../../includes/minishell.h"

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

int	change_token(t_lexer *new)
{
	if ((new->token % 2) != 0)
		return (WORD);
	else
		return (find_token(new->element));
}

bool	change_bool(bool quote, t_lexer *new)
{
	new->token += 1;
	if (quote == true)
		quote = false;
	else
		quote = true;
	return (quote);
}
