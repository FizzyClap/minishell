/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_other.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 08:54:38 by roespici          #+#    #+#             */
/*   Updated: 2024/09/04 14:38:15 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	builtin_echo(char **args)
{
	int	newline;
	int	i;

	newline = 1;
	i = 1;
	while (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
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

void	builtin_exit(char **args)
{
	int	exit_code;

	exit_code = 0;
	if (args[1])
		exit_code = ft_atoi(args[1]);
	free_split(args);
	exit(exit_code);
}