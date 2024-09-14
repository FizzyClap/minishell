#include "../../includes/minishell.h"

/*		ISIG	When any of the characters INTR, QUIT, SUSP, or DSUSP are
				received, generate the corresponding signal.

		STRUCTURE DES TERMIOS: termios_p

		tcflag_t	c_iflag;		 input modes 
		tcflag_t	c_oflag;		 output modes 
		tcflag_t	c_cflag;		 control modes 
		tcflag_t	c_lflag;		 local modes 
		cc_t		c_cc[NCCS];		 special characters
	
int tcgetattr(int fd, struct termios *termios_p);
int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);

CTRL-C :
- prompt vide: ^C + retour a la ligne + code 130;
- prompt rempli: ``                  ``         ;
- heredoc en cours: ^C + sorti du heredoc + code 130;
- processus en cours: ^C + sorti du processus + code 130;

CTRL-D :
- prompt vide: \nexit + code 0;
- prompt rempli: nothing;
- heredoc en cours: sorti du heredoc + juste la 1re ligne en historique + code 0;
- processus en cours: nothing;
	
CTRL-\ :
- prompt vide: nothing;
- prompt rempli: nothing;
- heredoc en cours: nothing;
- processus en cours: sorti du processus + "^\Quit  (core dumped)" + code 131;*/

void	set_termios(bool set)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	if (set == true)
		term.c_lflag |= ECHOCTL;
	else if (set == false)
		term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	ft_ctrl_c(int signum)
{
	if (signum == 2)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_code = 130;
	}
}

void	ft_ctrl_bs(int signum)
{
	if (signum == 3)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_ctrld(char *line)
{
	free(line);
	rl_clear_history();
	printf("exit\n");
	exit (EXIT_SUCCESS);
}
