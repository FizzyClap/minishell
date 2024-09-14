/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 09:42:34 by roespici          #+#    #+#             */
/*   Updated: 2024/09/14 14:59:53 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code = 0;

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
