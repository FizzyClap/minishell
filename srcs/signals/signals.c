#include "../../includes/minishell.h"

void	signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_ctrl_c);
}

void	ft_ctrld(char *line)
{
	free(line);
	rl_clear_history();
	printf("exit\n");
	exit (EXIT_SUCCESS);
}

void	ft_ctrl_c(int signum)
{
	if (signum == 2)
	{
		g_exit_code = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	here_signals()
{
	signal(SIGQUIT, ft_ctrl_bs_hd);
	signal(SIGINT, ft_ctrl_c_hd);
}

void	ft_ctrl_c_hd(int signum)
{
	if (signum == 2)
	{
		printf("\33[2K\r");
		exit(g_exit_code);
	}
}

