#include "../../includes/minishell.h"

static int	equal_pos_exist(t_env *new, char *equal_pos);

t_env	*create_node(char *env_line)
{
	t_env	*new;
	char	*equal_pos;

	if (!env_line)
		return (NULL);
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->line = ft_strdup(env_line);
	if (!new->line)
		return (free(new), NULL);
	new->next = NULL;
	equal_pos = ft_strchr(new->line, '=');
	if (!equal_pos)
	{
		new->var = ft_strdup(new->line);
		if (!new->var)
			return (free(new->line), free(new), NULL);
		new->token = 0;
		new->args = NULL;
		return (new);
	}
	if (equal_pos_exist(new, equal_pos) == FAILURE)
		return (NULL);
	return (new);
}

static int	equal_pos_exist(t_env *new, char *equal_pos)
{
	new->var = ft_substr(new->line, 0, equal_pos - new->line);
	if (!new->var)
		return (free(new->line), free(new), FAILURE);
	new->token = 1;
	new->args = ft_substr(equal_pos + 1, 0, ft_strlen(equal_pos + 1));
	if (!new->args)
		return (free(new->var), free(new->line), free(new), FAILURE);
	return (SUCCESS);
}

void	add_node(t_env **head, char *env_line)
{
	t_env	*new;
	t_env	*current;

	current = *head;
	new = create_node(env_line);
	if (!new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

void	modify_node(t_env *env, char *env_line)
{
	char	*new_args;
	char	*equal_pos;

	equal_pos = ft_strchr(env_line, '=');
	if (!equal_pos)
		return ;
	new_args = ft_strdup(equal_pos + 1);
	if (!new_args)
		return ;
	while (env)
	{
		if (ft_strncmp(env->var, env_line, equal_pos - env_line) == 0)
		{
			free(env->args);
			free(env->line);
			env->line = ft_strdup(env_line);
			if (!env->line)
				return (free(new_args));
			env->args = new_args;
			return ;
		}
		env = env->next;
	}
	free(new_args);
}

void	swap_nodes(t_env *node1, t_env *node2)
{
	char	*temp_line;
	char	*temp_var;
	char	*temp_args;
	int		temp_token;

	temp_line = node1->line;
	temp_var = node1->var;
	temp_args = node1->args;
	temp_token = node1->token;
	node1->line = node2->line;
	node1->var = node2->var;
	node1->args = node2->args;
	node1->token = node2->token;
	node2->line = temp_line;
	node2->var = temp_var;
	node2->args = temp_args;
	node2->token = temp_token;
}
