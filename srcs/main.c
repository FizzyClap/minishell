#include "../includes/minishell.h"

int	g_exit_code = 0;

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
