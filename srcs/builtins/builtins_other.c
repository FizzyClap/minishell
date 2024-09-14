/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_other.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoy <ggoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 08:54:38 by roespici          #+#    #+#             */
/*   Updated: 2024/09/13 12:00:01 by ggoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	cd_2_args(t_env *env, char **args, int fd);

void	builtin_echo(t_cmd *command, int fd)
{
	int	newline;
	int	i;

	newline = 1;
	i = 1;
	while (command->args[i] && ft_strcmp(command->args[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (command->args[i])
	{
		if (ft_strcmp(command->args[i], "$?") == 0)
			ft_putnbr_fd(g_exit_code, fd);
		else
			ft_putstr_fd(command->args[i], fd);
		if (command->args[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', fd);
}

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
	char	*prev_path;

	temp = getcwd(NULL, 0);
	if (!temp)
		temp = ft_strdup(get_env(env, "PWD"));
	if (ft_strcmp(args[1], "-") == 0)
	{
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

void	builtin_pwd(t_env *env, char **args, int fd)
{
	char	*cwd;
	char	*path_pwd;
	int		nb_args;

	nb_args = ft_count_args(args);
	if (nb_args > 1)
	{
		ft_putstr_fd("pwd: too many arguments\n", fd);
		return ;
	}
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

void	builtin_exit(t_env *env, t_cmd *command, char *line)
{
	int	nb_args;

	nb_args = ft_count_args(command->args);
	printf("exit\n");
	if (nb_args > 2)
	{
		printf("bash: exit: too many arguments\n");
		g_exit_code = 1;
		return ;
	}
	else if (nb_args == 2)
	{
		g_exit_code = ft_atoi(command->args[1]) % 256;
		if (!ft_strisnum(command->args[1]))
		{
			printf("bash: exit: %s: numeric argument required\n",
				command->args[1]);
			g_exit_code = 2;
		}
	}
	free_cmd(command);
	free_env(env);
	free(line);
	exit(g_exit_code);
}
