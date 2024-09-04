/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 09:42:34 by roespici          #+#    #+#             */
/*   Updated: 2024/09/04 16:49:26 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_builtins(t_env *env, char *line, char **args)
{
	args = ft_split(line, ' ');
	if (ft_strcmp(args[0], "echo") == 0)
		builtin_echo(args);
	else if (ft_strcmp(args[0], "cd") == 0)
		builtin_cd(args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(args[0], "export") == 0)
		builtin_export(env, args);
	else if (ft_strcmp(args[0], "unset") == 0)
		builtin_unset(env, args);
	else if (ft_strcmp(args[0], "env") == 0)
		builtin_env(env, args[0]);
	else if (ft_strcmp(args[0], "exit") == 0)
		builtin_exit(env, args);
	else
		printf("Fraudistan Inc: command not found: %s\n", args[0]);
	free_split(args);
}

int	main(void)
{
	t_command	command;
	t_env		*env;

	env = NULL;
	init_env(&env);
	while (1)
	{
		command.line = readline("Fraudistan> ");
		if (!command.line)
			break ;
		if (is_builtins(command.line))
			execute_builtins(env, command.line, command.args);
		free(command.line);
	}
}
