#include "../../includes/minishell.h"

static int	ft_bonjour(char *line, int i)
{
	if (i > 1 && line[i - 1] == '$' && line[i] == '?')
		return (1);
	else if (ft_chrinstr(" \"\'$", line[i]) != 0)
		return (1);
	else
		return (0);
}

static int	ft_connard(char *line, int i)
{
	while (line[i] && ft_bonjour(line, i) != 0)
	{
		i++;
		if (line[i - 1] == '?' && line [i - 2] == '$')
			return (i);
	}
	return (i);
}

static char	*zboub(char *line, int dup, int i, int start)
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

static t_var	*add_var(t_env *env, char *line, int i)
{
	t_var	*new;
	char	*tmp;
	int		dup;
	int		start;

	dup = 0;
	i++;
	if (line[i] == '?')
	{
		new = var_new(ft_itoa(g_exit_code), true);
		return (new);
	}
	start = i;
	while (line[i] && ft_chrinstr(" $\'\"", line[i]) != 0)
	{
		i++;
		dup++;
	}
	tmp = zboub(line, dup, i, start);
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
			i = ft_connard(line, i);
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
			i = ft_connard(line, i);
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
	free(line);
	return (result);
}
