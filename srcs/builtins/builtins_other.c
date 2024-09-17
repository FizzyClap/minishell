#include "../../includes/minishell.h"

static int	arg_is_valid(char *arg);

void	builtin_echo(t_cmd *command, int fd)
{
	int	newline;
	int	i;

	newline = 1;
	i = 1;
	while (command->args[i] && arg_is_valid(command->args[i]) == SUCCESS)
	{
		newline = 0;
		i++;
	}
	while (command->args[i])
	{
		if (ft_strcmp(command->args[i], "$?") == 0)
			ft_putnbr_fd(g_exit_code, fd);
		ft_putstr_fd(command->args[i], fd);
		if (command->args[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', fd);
}

static int	arg_is_valid(char *arg)
{
	int	i;

	if (!arg[0])
		return (FAILURE);
	i = -1;
	while (arg[++i])
	{
		if (arg[0] != '-')
			return (FAILURE);
		if (i >= 1 && arg[i] != 'n')
			return (FAILURE);
	}
	return (SUCCESS);
}

void	builtin_pwd(t_env *env, int fd)
{
	char	*cwd;
	char	*path_pwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_fprintf(fd, "%s\n", cwd);
		return (free(cwd));
	}
	path_pwd = get_env(env, "PWD");
	if (path_pwd)
		ft_fprintf(fd, "%s\n", path_pwd);
}

void	builtin_exit(t_env *env, t_cmd *command)
{
	int	nb_args;

	nb_args = ft_count_args(command->args);
	printf("exit\n");
	if (nb_args > 2)
	{
		ft_fprintf(STDERR_FILENO, "Fraudistan: exit: too many arguments\n");
		g_exit_code = EXIT_FAILURE;
		return ;
	}
	else if (nb_args == 2)
	{
		g_exit_code = ft_atoi(command->args[1]) % 256;
		if (!ft_strisnum(command->args[1]))
		{
			ft_fprintf(STDERR_FILENO, "Fraudistan: exit: %s: numeric argument "
			"required\n", command->args[1]);
			g_exit_code = EXIT_SYNTAX_ERROR;
		}
	}
	free_cmd(command);
	free_env(env);
	exit(g_exit_code);
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
