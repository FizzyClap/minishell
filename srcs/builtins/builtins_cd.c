#include "../../includes/minishell.h"

static void	cd_2_args(t_env *env, char **args, int fd);
static void	cd_prev_path(t_env *env, int fd);
static void	cd_new_path(t_env *env, char **args);
static void	set_env(t_env *env, char *var_name, char *new_path);

void	builtin_cd(t_env *env, char **args, int fd)
{
	char		*path_to_home;
	char		*temp;
	int			nb_args;

	path_to_home = NULL;
	nb_args = ft_count_args(args);
	if (nb_args > 2)
	{
		ft_fprintf(STDERR_FILENO, "Fraudistan: cd: too many arguments\n");
		g_exit_code = EXIT_FAILURE;
	}
	if (nb_args == 1 || (nb_args == 2 && ft_strcmp(args[1], "--") == 0))
	{
		path_to_home = getenv("HOME");
		temp = getcwd(NULL, 0);
		if (!temp)
			return ;
		if (path_to_home && chdir(path_to_home) == FAILURE)
			perror("Fraudistan: cd: ");
		set_env(env, "PWD", path_to_home);
		set_env(env, "OLDPWD", temp);
		free(temp);
	}
	else if (nb_args == 2)
		cd_2_args(env, args, fd);
}

static void	cd_2_args(t_env *env, char **args, int fd)
{
	char	*temp;

	temp = getcwd(NULL, 0);
	if (!temp)
	{
		temp = ft_strdup(get_env(env, "PWD"));
		if (!temp)
			return ;
	}
	if (ft_strcmp(args[1], "-") == 0)
		cd_prev_path(env, fd);
	else
		cd_new_path(env, args);
	set_env(env, "OLDPWD", temp);
	free(temp);
}

static void	cd_prev_path(t_env *env, int fd)
{
	char	*prev_path;

	prev_path = get_env(env, "OLDPWD");
	if (prev_path)
	{
		if (chdir(prev_path) == FAILURE)
		{
			ft_fprintf(STDERR_FILENO, "Fraudistan: cd: %s: ", prev_path);
			g_exit_code = 1;
			return (perror(""));
		}
		ft_fprintf(fd, "%s\n", prev_path);
		set_env(env, "PWD", prev_path);
	}
}

static void	cd_new_path(t_env *env, char **args)
{
	char	*new_path;

	new_path = NULL;
	if (chdir(args[1]) == FAILURE)
	{
		ft_fprintf(STDERR_FILENO, "Fraudistan: cd: %s: ", args[1]);
		g_exit_code = 1;
		return (perror(""));
	}
	new_path = getcwd(NULL, 0);
	set_env(env, "PWD", new_path);
	free(new_path);
}

static void	set_env(t_env *env, char *var_name, char *new_path)
{
	while (env)
	{
		if (ft_strcmp(env->var, var_name) == 0)
		{
			free(env->args);
			env->args = ft_strdup(new_path);
			return ;
		}
		env = env->next;
	}
}
