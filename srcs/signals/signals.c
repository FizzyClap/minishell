/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:05:15 by roespici          #+#    #+#             */
/*   Updated: 2024/09/17 15:11:36 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ctrl_c(int signum);
static void	ctrl_c_hd(int signum);

void	signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c);
}

void	ctrl_d(char *line)
{
	free(line);
	rl_clear_history();
	printf("exit\n");
	exit (EXIT_SUCCESS);
}

void	here_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c_hd);
}

static void	ctrl_c(int signum)
{
	if (signum == 2)
	{
		g_exit_code = EXIT_SIGINT;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	ctrl_c_hd(int signum)
{
	if (signum == 2)
	{
		printf("\33[2K\r");
		exit(g_exit_code);
	}
}
