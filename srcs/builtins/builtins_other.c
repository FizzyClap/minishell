/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_other.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 08:54:38 by roespici          #+#    #+#             */
/*   Updated: 2024/09/10 11:59:12 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if (nb_args == 1)
	{
		path_to_home = getenv("HOME");
		env->prev_path = getcwd(NULL, 0);
		if (path_to_home)
			if (chdir(path_to_home) == FAILURE)
				perror("chdir error");
	}
	else if (nb_args == 2)
	{
		temp = getcwd(NULL, 0);
		if (ft_strcmp(args[1], "-") == 0)
		{
			ft_putstr_fd(env->prev_path, fd);
			ft_putchar_fd('\n', fd);
			if (chdir(env->prev_path) == FAILURE)
				perror("chdir error");
		}
		else if (chdir(args[1]) == FAILURE)
			perror("chdir error");
		env->prev_path = ft_strdup(temp);
		free(temp);
	}
}

void	builtin_pwd(char **args, int fd)
{
	char	*cwd;
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
		ft_putstr_fd(cwd, fd);
		ft_putchar_fd('\n', fd);
		free(cwd);
	}
	else
		perror("getcwd error");
}

void	builtin_exit(t_env *env, t_cmd *command)
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
	free_env(env);
	exit(g_exit_code);
}
