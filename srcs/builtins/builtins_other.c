/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_other.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 08:54:38 by roespici          #+#    #+#             */
/*   Updated: 2024/09/06 09:11:46 by roespici         ###   ########.fr       */
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

void	builtin_cd(char **args)
{
	char	*path_to_home;

	path_to_home = NULL;
	if (!args[1])
	{
		path_to_home = getenv("HOME");
		if (path_to_home)
			if (chdir(path_to_home) == FAILURE)
				perror("chdir error");
	}
	else
	{
		if (chdir(args[1]) == FAILURE)
			perror("chdir error");
	}
}

void	builtin_pwd(void)
{
	char	*cwd;

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
	if (nb_args == 2)
		command->exit_code = ft_atoi(command->args[1]) % 256;
	printf("exit\n");
	if (nb_args > 2)
	{
		printf("bash: exit: too many arguments\n");
		command->exit_code = 1;
		return ;
	}
	free_env(env);
	free_split(command->args);
	exit(command->exit_code);
}
