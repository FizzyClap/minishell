/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 11:53:28 by ggoy              #+#    #+#             */
/*   Updated: 2024/09/14 17:25:04 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_var	*add_var(t_env *env, char *line, int i)
{
	t_var	*new;
	char	*tmp;
	int		dup;
	int		temp;

	dup = 0;
	i++;
	temp = i;
	while (line[i] && ft_chrinstr(" $\'\"", line[i]) != 0)
	{
		i++;
		dup++;
	}
	tmp = ft_calloc(dup + 1, sizeof(char));
	dup = 0;
	while (temp < i)
	{
		tmp[dup] = line[temp];
		dup++;
		temp++;
	}
	new = var_new(get_env(env, tmp), true);
	if (!new->variable)
		new->exist = ft_change_bool(new->exist);
	return (free(tmp), new);
}

static t_var	*get_vars(char *line, t_env *env)
{
	t_var	*vars;
	bool	quote;
	int		i;

	quote = false;
	i = -1;
	vars = NULL;
	while (line[++i])
	{
		if (line[i] == '\'')
			quote = ft_change_bool(quote);
		if (line[i] && line[i] == '$' && quote == false)
		{
			var_add_back(&vars, add_var(env, line, i));
			while (line[i] && ft_chrinstr(" $\'\"", line[i]) != 0)
				i++;
		}
		if (!line[i])
			break ;
	}
	return (vars);
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
	bool	quote;
	int		i;
	int		j;

	quote = false;
	i = 0;
	j = 0;
	new = NULL;
	while (line[i])
	{
		if (line[i] == '\'')
			quote = ft_change_bool(quote);
		if (line[i] && line[i] == '$' && quote == false)
		{
			i++;
			new = ft_strjoin(new, vars->variable);
			vars = vars->next;
			while (line[i] && ft_chrinstr(" $\'\"", line[i]) != 0)
				i++;
		}
		if (line[i] && (line[i] != '$' || quote == true))
			new = join_char(new, line[i++]);
	}
	return (new);
}

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
	return (result);
}
