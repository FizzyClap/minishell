/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:30:23 by roespici          #+#    #+#             */
/*   Updated: 2024/09/14 10:35:25 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	cd_2_args(t_env *env, char **args, int fd);
static void	cd_prev_path(t_env *env, int fd);
static void	set_env(t_env *env, char *var_name, char *new_path);

void	builtin_cd(t_env *env, char **args, int fd)
{
	char		*path_to_home;
	char		*temp;
	int			nb_args;

	path_to_home = NULL;
	nb_args = ft_count_args(args);
	if (nb_args > 2)
		printf("bash: cd: too many arguments\n");
	if (nb_args == 1 || (nb_args == 2 && ft_strcmp(args[1], "--") == 0))
	{
		path_to_home = getenv("HOME");
		temp = getcwd(NULL, 0);
		if (!temp)
			return ;
		if (path_to_home && chdir(path_to_home) == FAILURE)
			perror("bash: cd: ");
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
	char	*path_to_pwd;

	temp = getcwd(NULL, 0);
	if (!temp)
	{
		path_to_pwd = get_env(env, "PWD");
		temp = ft_strdup(path_to_pwd);
		if (!temp)
			return ;
	}
	if (ft_strcmp(args[1], "-") == 0)
		cd_prev_path(env, fd);
	else
	{
		if (chdir(args[1]) == FAILURE)
		{
			ft_fprintf(STDERR_FILENO, "bash: cd: %s: ", args[1]);
			g_exit_code = 1;
			return (perror(""));
		}
		set_env(env, "PWD", getcwd(NULL, 0));
	}
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
			ft_fprintf(STDERR_FILENO, "bash: cd: %s: ", prev_path);
			g_exit_code = 1;
			return (perror(""));
		}
		ft_fprintf(fd, "%s\n", prev_path);
		set_env(env, "PWD", prev_path);
	}
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