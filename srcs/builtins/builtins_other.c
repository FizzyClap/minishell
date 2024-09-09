/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_other.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 08:54:38 by roespici          #+#    #+#             */
/*   Updated: 2024/09/09 14:21:44 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_echo(t_cmd *command)
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
			printf("%d", command->exit_code);
		else
			printf("%s", command->args[i]);
		if (command->args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}

void	builtin_cd(t_env *env, char **args)
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
			if (chdir(env->prev_path) == FAILURE)
				perror("chdir error");
			printf("%s\n", env->prev_path);
		}
		else if (chdir(args[1]) == FAILURE)
			perror("chdir error");
		env->prev_path = ft_strdup(temp);
		free(temp);
	}
}

void	builtin_pwd(char **args)
{
	char	*cwd;
	int		nb_args;

	nb_args = ft_count_args(args);
	if (nb_args > 1)
	{
		printf("pwd: too many arguments\n");
		return ;
	}
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
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
		command->exit_code = 1;
		return ;
	}
	else if (nb_args == 2)
	{
		command->exit_code = ft_atoi(command->args[1]) % 256;
		if (!ft_strisnum(command->args[1]))
		{
			printf("bash: exit: %s: numeric argument required\n",
				command->args[1]);
			command->exit_code = 2;
		}
	}
	free_env(env);
	exit(command->exit_code);
}
