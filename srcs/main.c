/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoy <ggoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 09:42:34 by roespici          #+#    #+#             */
/*   Updated: 2024/09/14 12:00:21 by ggoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code = 0;

void	execute_builtins(t_env *env, t_cmd *command, int fd)
{
	if (ft_strcmp(command->cmd, "echo") == 0)
		builtin_echo(command, fd);
	else if (ft_strcmp(command->cmd, "cd") == 0)
		builtin_cd(env, command->args, fd);
	else if (ft_strcmp(command->cmd, "pwd") == 0)
		builtin_pwd(env, command->args, fd);
	else if (ft_strcmp(command->cmd, "export") == 0)
		builtin_export(env, command, fd);
	else if (ft_strcmp(command->cmd, "unset") == 0)
		builtin_unset(env, command->args);
	else if (ft_strcmp(command->cmd, "env") == 0)
		builtin_env(env, command->cmd, fd);
	else if (ft_strcmp(command->cmd, "exit") == 0)
		builtin_exit(env, command);
	else
		printf("%s: command not found\n", command->cmd);
}

static t_cmd	*prompt_loop(char *line)
{
	t_lexer		*lexer;
	t_lexer		*lex_redir;
	t_split_cmd	*split;
	t_cmd		*final;

	final = NULL;
	lexer = make_lexer(line);
	if (lexer == NULL)
		return (NULL);
	lex_redir = clean_redir(lexer);
	if (lex_redir == NULL)
		return (NULL);
	free_lexer(lexer);
	split = split_cmd(lex_redir);
	free_lexer(lex_redir);
	final = make_cmd(split);
	free_split_cmd(split);
	return (final);
}

int	main(void)
{
	t_cmd	*command;
	t_env	*env;
	char	*line;

	env = NULL;
	init_env(&env);
	signal(SIGINT, ft_ctrl_c);
	signal(SIGQUIT, ft_ctrl_bs);
	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
			ft_ctrld(line);
		if (ft_strlen(line))
		{
			add_history(line);
			line = parsing_env(line, env);
			command = prompt_loop(line);
			if (command)
				execute_pipeline(command, env);
			free_cmd(command);
		}
		free(line);
	}
}
