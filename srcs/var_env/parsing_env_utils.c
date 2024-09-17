/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:05:20 by roespici          #+#    #+#             */
/*   Updated: 2024/09/17 14:23:56 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_quote	strct_bool_change(t_quote quote, char c)
{
	if (c == '\'' && quote.d_quote == false)
		quote.quote = ft_change_bool(quote.quote);
	else if (c == '\"' && quote.quote == false)
		quote.d_quote = ft_change_bool(quote.d_quote);
	return (quote);
}

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
	if (i > 0 && line[i - 1] == '$' && line[i] == '$')
		return (i + 1);
	else if (i > 0 && line[i] == '?' && line [i - 1] == '$')
		return (i + 1);
	while (line[i] && check_chr(line, i) != 0)
		i++;
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

t_var	*var_exceptions(t_var *new, char *line, int i)
{
	char	*tmp;

	if (line[i] == '?')
	{
		tmp = ft_itoa(g_exit_code);
		new = var_new(tmp, true);
		free(tmp);
		return (new);
	}
	else if (line [i] == '$')
	{
		tmp = ft_itoa(getpid());
		new = var_new(tmp, true);
		free(tmp);
		return (new);
	}
	else
		return (NULL);
}
