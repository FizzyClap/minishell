#include "../../includes/minishell.h"

int	check_chr(char *line, int i)
{
	if (i > 1 && line[i - 1] == '$' && line[i] == '?')
		return (1);
	else if (ft_chrinstr(" \"\'$", line[i]) != 0)
		return (1);
	else
		return (0);
}

int	progress(char *line, int i)
{
	while (line[i] && check_chr(line, i) != 0)
	{
		i++;
		if (line[i - 1] == '?' && line [i - 2] == '$')
			return (i);
	}
	return (i);
}

char	*dup_tmp(char *line, int dup, int i, int start)
{
	char	*tmp;

	tmp = ft_calloc(dup + 1, sizeof(char));
	dup = 0;
	while (start < i)
	{
		tmp[dup] = line[start];
		dup++;
		start++;
	}
	return (tmp);
}

t_quote	strct_bool_change(t_quote quote, char c)
{
	if (c == '\'' && quote.d_quote == false)
		quote.quote = ft_change_bool(quote.quote);
	else if (c == '\"' && quote.quote == false)
		quote.d_quote = ft_change_bool(quote.d_quote);
	return (quote);
}