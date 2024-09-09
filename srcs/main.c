/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartan <gartan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 09:42:34 by roespici          #+#    #+#             */
/*   Updated: 2024/09/09 17:14:22 by gartan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code;

void	execute_builtins(t_env *env, t_cmd *command)
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
}

void print_lexer(t_lexer *lex)
{
	while (lex)
	{
		printf("%i %s\n", lex->token, lex->element);
		lex = lex->next;
	}
}

void print_split(t_split_cmd *split)
{
	t_lexer *lex;
	int		i;

	i = 0;
	while (split)
	{
		printf("Split %d:\n", i);
		lex = split->cmd;
		while (lex)
		{
			printf("   %i %s\n", lex->token, lex->element);
			lex = lex->next;
		}
		split = split->next;
		i++;
	}
}

static void	ft_ctrl(int signum)
{
	if (signum == 2)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_code = 130;
	}
	if (signum == 3)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	ft_ctrld(void)
{
	rl_clear_history();
	printf("exit\n");
	exit (EXIT_SUCCESS);
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
	init_minishell(&env);
	signal(SIGINT, ft_ctrl);
	signal(SIGQUIT, ft_ctrl);
	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
			ft_ctrld();
		if (ft_strlen(line))
		{
			command = prompt_loop(line);
			add_history(line);
		}
		if (command)
		{
			execute_pipex(command, env);
			free_cmd(command);
		}
		//else
		//{
		//	init_pipex(&pipex, &command, env);
		//	free_split(command.args);
		//}
		free(line);
	}
}
