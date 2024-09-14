/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_other.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 08:54:38 by roespici          #+#    #+#             */
/*   Updated: 2024/09/14 13:13:31 by roespici         ###   ########.fr       */
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
		ft_putstr_fd(command->args[i], fd);
		if (command->args[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', fd);
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
	free_cmd(command);
	free_env(env);
	exit(g_exit_code);
}
