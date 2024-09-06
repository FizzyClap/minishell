/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 09:42:34 by roespici          #+#    #+#             */
/*   Updated: 2024/09/06 09:15:28 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	execute_builtins(t_env *env, t_cmd *command)
{
	if (ft_strcmp(command->args[0], "echo") == 0)
		builtin_echo(command);
	else if (ft_strcmp(command->args[0], "cd") == 0)
		builtin_cd(command->args);
	else if (ft_strcmp(command->args[0], "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(command->args[0], "export") == 0)
		builtin_export(env, command->args);
	else if (ft_strcmp(command->args[0], "unset") == 0)
		builtin_unset(env, command->args);
	else if (ft_strcmp(command->args[0], "env") == 0)
		builtin_env(env, command->args[0]);
	else if (ft_strcmp(command->args[0], "exit") == 0)
		builtin_exit(env, command);
	else
		printf("%s: command not found\n", command->args[0]);
	free_split(command->args);
}

static void	prompt_loop(char *line)
{
	t_lexer		*lexer;
	t_lexer		*lex_redir;
	t_split_cmd	*split;
	t_cmd	*final;
	int			i;
	int			j;

	lexer = make_lexer(line);
	lex_redir = clean_redir(lexer);
	split = split_cmd(lex_redir);
	final = make_cmd(split);
	printf("\n -----  FINAL COMMAND  ----- \n\n");
	i = 1;
	printf("%s\n", line);
	while (final)
	{
		j = -1;
		printf("\nCommande: %i\n", i);
		printf("command: %s\n", final->cmd);
		while (final->args && final->args[++j])
			printf("arguments %i: %s\n", j, final->args[j]);
		j = 1;
		while (final->output_redirection)
		{
			printf("redirections %i:\nelement: %s token: %i\n", j, final->output_redirection->element, final->output_redirection->token);
			final->output_redirection = final->output_redirection->next;
			j++;
		}
		final = final->next;
		i++;
	}
}

int	main(void)
{
	t_cmd	command;
	t_pipex	pipex;
	t_env	*env;

	env = NULL;
	init_minishell(&env, &command);
	while (1)
	{
		command.line = readline(PROMPT);
		if (!command.line)
			break ;
		prompt_loop(command.line);
		add_history(command.line);
		command.args = ft_split(command.line, ' ');
		command.exit_code = 0;
		if (is_builtins(command.line))
			execute_builtins(env, &command);
		else
		{
			init_pipex(&pipex, &command, env);
			free_split(command.args);
		}
		free(command.line);
	}
}
