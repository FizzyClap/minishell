/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:37:15 by roespici          #+#    #+#             */
/*   Updated: 2024/09/02 09:10:09 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	fill_here_doc(t_pipex *pipex, char *limiter)
{
	char	*line;

	pipex->infile = open("here_doc.tmp", O_CREAT | O_WRONLY, 0644);
	if (pipex->infile < 0)
		error_exit("Here_doc error");
	while (1)
	{
		ft_putstr("pipe heredoc> ");
		line = get_next_line(STDIN_FILENO);
		if (ft_strcmp(line, limiter) == 10)
		{
			free(line);
			break ;
		}
		if (pipex->outfile_open)
			ft_putstr_fd(line, pipex->infile);
		free(line);
	}
	close(pipex->infile);
}

static void	exec_here_doc(t_pipex *pipex, char **argv)
{
	pipex->infile = open("here_doc.tmp", O_RDONLY);
	execute_pipes(pipex, argv, 3);
}

static void	close_here_doc(t_pipex *pipex)
{
	close_pipes(pipex);
	unlink("here_doc.tmp");
}

void	here_doc(t_pipex *pipex, char *limiter, int argc, char **argv)
{
	int	i;
	int	last_arg;

	i = -1;
	last_arg = argc - 1;
	open_outfile(pipex, argc, argv);
	fill_here_doc(pipex, limiter);
	if (!pipex->outfile_open)
	{
		ft_printf("zsh: permission denied: %s\n", argv[last_arg]);
		unlink("here_doc.tmp");
		return ;
	}
	exec_here_doc(pipex, argv);
	while (++i <= pipex->nb_pipes)
		waitpid(pipex->child[i], &pipex->status, 0);
	close_here_doc(pipex);
}
