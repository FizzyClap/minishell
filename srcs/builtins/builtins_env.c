#include "../../includes/minishell.h"

static int	arg_is_exportable(char *str);
static void	sort_and_print(t_env *env, t_cmd *cmd, int fd);
static void	sort_env(t_env *env);

void	builtin_export(t_env *env, t_cmd *cmd, int fd)
{
	t_env	*current;
	bool	var_exist;
	int		i;

	i = 0;
	while (cmd->args[++i])
	{
		var_exist = false;
		current = env;
		while (current)
		{
			if (arg_is_exportable(cmd->args[i]) == FAILURE)
			{
				ft_fprintf(STDERR_FILENO, "Fraudistan: export: %s: not a valid identifier\n", cmd->args[i]);
				g_exit_code = EXIT_FAILURE;
				return ;
			}
			if (ft_strncmp(current->var, cmd->args[i], \
				ft_strchr(cmd->args[i], '=') - cmd->args[i]) == 0)
			{
				var_exist = true;
				if (ft_strchr(cmd->args[i], '='))
					modify_node(current, cmd->args[i]);
				break ;
			}
			if (!current->next && var_exist == false)
				add_node(&current, cmd->args[i]);
			current = current->next;
		}
	}
	sort_and_print(env, cmd, fd);
}

static int	arg_is_exportable(char *str)
{
	int	i;
	int	len;

	if (!str || str[0] == '=')
		return (FAILURE);
	i = -1;
	if (ft_strchr(str, '='))
		len = ft_strchr(str, '=') - str;
	else
		len = ft_strlen(str);
	while (++i < len)
	{
		if (str[0] >= '0' && str[0] <= '9')
			return (FAILURE);
		if (!ft_isalnum(str[i]))
			return (FAILURE);
	}
	return (SUCCESS);
}
void	builtin_unset(t_env *env, char **args)
{
	t_env	*current;
	t_env	*prev;
	t_env	*temp;
	int		i;

	i = 0;
	while (args[++i])
	{
		current = env;
		while (current->next)
		{
			if (ft_strcmp(current->next->var, args[i]) == 0)
			{
				prev = current;
				temp = current->next;
				prev->next = current->next->next;
				free(temp->line);
				free(temp->var);
				free(temp->args);
				free(temp);
			}
			else
				current = current->next;
		}
	}
}

void	builtin_env(t_env *head, t_cmd *cmd, int fd)
{
	t_env	*current;
	int		nb_args;

	nb_args = ft_count_args(cmd->args);
	if (ft_strcmp(cmd->cmd, "env") == 0 && nb_args > 1)
	{
		ft_putstr_fd("Fraudistan: env: too many arguments\n", STDERR_FILENO);
		return ;
	}
	current = head;
	while (current)
	{
		if (ft_strcmp(cmd->cmd, "export") == 0)
		{
			ft_putstr_fd("declare -x ", fd);
			if (current->token)
				ft_fprintf(fd, "%s=\"%s\"\n", current->var, current->args);
			else
				ft_fprintf(fd, "%s\n", current->var);
		}
		else if (current->token)
			ft_fprintf(fd, "%s=%s\n", current->var, current->args);
		current = current->next;
	}
}

static void	sort_and_print(t_env *env, t_cmd *cmd, int fd)
{
	t_env	*sorted_env;
	int		nb_args;

	nb_args = ft_count_args(cmd->args);
	if (ft_strcmp(cmd->cmd, "export") == 0 && nb_args == 1)
	{
		sorted_env = copy_env(env);
		sort_env(sorted_env);
		builtin_env(sorted_env, cmd, fd);
		free_env(sorted_env);
	}
}

static void	sort_env(t_env *env)
{
	t_env	*current_node;
	t_env	*next_node;
	t_env	*min_node;

	current_node = env;
	while (current_node)
	{
		min_node = current_node;
		next_node = current_node->next;
		while (next_node)
		{
			if (ft_strcmp(next_node->var, min_node->var) < 0)
				min_node = next_node;
			next_node = next_node->next;
		}
		if (min_node != current_node)
			swap_nodes(current_node, min_node);
		current_node = current_node->next;
	}
}
