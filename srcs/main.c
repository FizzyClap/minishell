/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 09:42:34 by roespici          #+#    #+#             */
/*   Updated: 2024/09/07 10:27:38 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	execute_builtins(t_env *env, t_cmd *command)
{
	if (ft_strcmp(command->cmd, "echo") == 0)
		builtin_echo(command);
	else if (ft_strcmp(command->cmd, "cd") == 0)
		builtin_cd(env, command->args);
	else if (ft_strcmp(command->cmd, "pwd") == 0)
		builtin_pwd(command->args);
	else if (ft_strcmp(command->cmd, "export") == 0)
		builtin_export(env, command->cmd, command->args);
	else if (ft_strcmp(command->cmd, "unset") == 0)
		builtin_unset(env, command->args);
	else if (ft_strcmp(command->cmd, "env") == 0)
		builtin_env(env, command->cmd);
	else if (ft_strcmp(command->cmd, "exit") == 0)
		builtin_exit(env, command);
	else
		printf("%s: command not found\n", command->cmd);
	free_split(command->args);
}

static t_cmd	*prompt_loop(char *line)
{
	t_lexer		*lexer;
	t_lexer		*lex_redir;
	t_split_cmd	*split;
	t_cmd		*final;

	final = NULL;
	lexer = make_lexer(line);
	lex_redir = clean_redir(lexer);
	split = split_cmd(lex_redir);
	final = make_cmd(split);
	final->line = ft_strdup(line);
	final->exit_code = 0;
	return (final);
}

int	main(void)
{
	t_cmd	*command;
	t_env	*env;
	char	*line;

	env = NULL;
	init_minishell(&env);
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
			break ;
		command = prompt_loop(line);
		add_history(command->line);
		if (is_builtins(command))
			execute_builtins(env, command);
		//else
		//{
		//	init_pipex(&pipex, &command, env);
		//	free_split(command.args);
		//}
		free(line);
	}
}
