/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:05:24 by roespici          #+#    #+#             */
/*   Updated: 2024/09/17 15:01:21 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_var	*get_vars(char *line, t_env *env);
static char		*replace_vars(char *line, t_var *vars);
static t_var	*add_var(t_env *env, char *line, int i);

char	*parsing_env(char *line, t_env *env)
{
	char	*result;
	t_var	*vars;
	t_var	*tmp;

	tmp = NULL;
	vars = NULL;
	result = NULL;
	vars = get_vars(line, env);
	tmp = vars;
	result = replace_vars(line, vars);
	free_vars(tmp);
	free(line);
	return (result);
}

static t_var	*get_vars(char *line, t_env *env)
{
	t_var	*vars;
	t_quote	quote;
	int		i;

	quote.quote = false;
	quote.d_quote = false;
	i = -1;
	vars = NULL;
	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			quote = strct_bool_change(quote, line[i]);
		else if (line[i + 1] && line[i + 1] != '\"' && \
			line[i] == '$' && quote.quote == false)
		{
			if (line[i + 1] != ' ')
				var_add_back(&vars, add_var(env, line, i));
			i = progress(line, i);
		}
		else if (!line[i])
			break ;
	}
	return (vars);
}

static t_var	*add_var(t_env *env, char *line, int i)
{
	t_var	*new;
	char	*tmp;
	int		dup;
	int		start;

	new = NULL;
	dup = 0;
	i++;
	new = var_exceptions(new, line, i);
	if (new == NULL)
	{
		start = i;
		while (line[i] && ft_chrinstr(" $\'\"", line[i]) != 0)
		{
			i++;
			dup++;
		}
		tmp = dup_tmp(line, dup, i, start);
		new = var_new(get_env(env, tmp), true);
		return (free(tmp), new);
	}
	else
		return (new);
}

static char	*join_char(char *str, char c)
{
	char	*new;
	int		i;

	i = -1;
	if (!str)
	{
		new = ft_calloc(sizeof(char), 2);
		new[0] = c;
		return (new);
	}
	new = ft_calloc(sizeof(char), ft_strlen(str) + 2);
	while (str[++i])
		new[i] = str[i];
	new[i] = c;
	return (free(str), new);
}

static char	*replace_vars(char *line, t_var *vars)
{
	char	*new;
	t_quote	quote;
	int		i;
	int		j;

	quote.quote = false;
	quote.d_quote = false;
	i = 0;
	j = 0;
	new = NULL;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			quote = strct_bool_change(quote, line[i]);
		if (line[i + 1] && line[i] == '$' && quote.quote == false && \
			line[i + 1] != ' ' && line[i + 1] != '\"' && ++i)
		{
			new = ft_strjoin(new, vars->variable);
			vars = vars->next;
			i = progress(line, i);
		}
		else if (line[i] || quote.quote == true)
			new = join_char(new, line[i++]);
	}
	return (new);
}
