/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 07:55:02 by roespici          #+#    #+#             */
/*   Updated: 2024/09/02 09:09:58 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	open_and_exec(t_pipex *pipex, int argc, char **argv)
{
	if (open_infile(pipex, argv) == FAILURE)
	{
		if (open_outfile(pipex, argc, argv) == FAILURE)
			return (FAILURE);
		execute_pipes(pipex, argv, 3);
	}
	else
	{
		open_outfile(pipex, argc, argv);
		execute_pipes(pipex, argv, 2);
	}
	return (SUCCESS);
}

int	execute_pipex(int argc, char **argv, char *const *envp)
{
	t_pipex	pipex;
	int		i;

	init_pipex(&pipex, argc, argv, envp);
	i = -1;
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		pipex.limiter = argv[2];
		here_doc(&pipex, pipex.limiter, argc, argv);
	}
	else
	{
		if (open_and_exec(&pipex, argc, argv) == FAILURE)
			return (free_pipex(&pipex), WEXITSTATUS(pipex.status));
		while (++i <= pipex.nb_pipes)
			waitpid(pipex.child[i], &pipex.status, 0);
	}
	return (free_pipex(&pipex), WEXITSTATUS(pipex.status));
}
