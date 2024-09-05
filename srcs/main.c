/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 09:42:34 by roespici          #+#    #+#             */
/*   Updated: 2024/09/05 11:50:30 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_builtins(t_env *env, char **args)
{
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

int	count_args(char **args)
{
	int	count;

	count = 1;
	while (args[count])
		count++;
	return (count);
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
		add_history(command.line);
		command.args = ft_split(command.line, ' ');
		if (is_builtins(command.line))
			execute_builtins(env, command.args);
		//else
		//	execute_pipex(count_args(command.args), command.args, env);
		free(command.line);
	}
}
