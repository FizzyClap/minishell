/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:05:50 by roespici          #+#    #+#             */
/*   Updated: 2024/09/17 15:10:14 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code = 0;

int	main(int argc, char **argv, char *const *envp)
{
	t_cmd	*command;
	t_env	*env;
	char	*line;

	(void)argc;
	(void)argv;
	env = NULL;
	init_env(&env, envp);
	while (1)
	{
		signals();
		line = readline(PROMPT);
		if (line == NULL)
			ctrl_d(line);
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
