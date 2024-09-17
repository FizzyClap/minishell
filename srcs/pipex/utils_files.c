/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:10:29 by roespici          #+#    #+#             */
/*   Updated: 2024/09/17 14:15:56 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	both_are_wrong(t_pipex *pipex, bool should_exit);

int	files_are_valid(t_pipex *pipex, bool should_exit)
{
	if (pipex->infile_error || pipex->outfile_error)
	{
		both_are_wrong(pipex, should_exit);
		if (pipex->infile_error)
		{
			open(pipex->infile_error->element, O_RDONLY);
			ft_fprintf(STDERR_FILENO, "Fraudistan: %s: ", \
			pipex->infile_error->element);
			perror("");
			if (should_exit == true)
				exit(EXIT_FAILURE);
		}
		if (pipex->outfile == FAILURE)
		{
			ft_fprintf(STDERR_FILENO, "Fraudistan: %s: Permission denied\n", \
				pipex->outfile_error);
			if (should_exit == true)
				exit(EXIT_FAILURE);
		}
		g_exit_code = EXIT_FAILURE;
		return (FAILURE);
	}
	return (SUCCESS);
}

static void	both_are_wrong(t_pipex *pipex, bool should_exit)
{
	if (pipex->infile_error && pipex->outfile_error)
	{
		if (pipex->infile_error->index < pipex->outfile_error->index)
		{
			open(pipex->infile_error->element, O_RDONLY);
			ft_fprintf(STDERR_FILENO, "Fraudistan: %s: ", \
			pipex->infile_error->element);
			perror("");
			if (should_exit == true)
				exit(EXIT_FAILURE);
		}
		ft_fprintf(STDERR_FILENO, "Fraudistan: %s: Permission denied\n", \
		pipex->outfile_error->element);
		if (should_exit == true)
			exit(EXIT_FAILURE);
	}
}

int	create_outfile(t_pipex *pipex, t_lexer *parse)
{
	if (parse->token == OUT && ((pipex->infile_error && \
	pipex->infile_error->index > parse->index) || !pipex->infile_error))
	{
		pipex->outfile = open(parse->element, \
		O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (access(parse->element, W_OK) == FAILURE)
		{
			pipex->outfile_error = parse;
			return (FAILURE);
		}
	}
	else if (parse->token == APPEND && ((pipex->infile_error && \
	pipex->infile_error->index > parse->index) || !pipex->infile_error))
	{
		pipex->outfile = open(parse->element, \
		O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (access(parse->element, W_OK) == FAILURE)
		{
			pipex->outfile_error = parse;
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

void	verif_is_executable(t_pipex *pipex)
{
	if (ft_strncmp(pipex->cmd->args[0], "./", 2) == 0 || \
		ft_strncmp(pipex->cmd->args[0], "/", 1) == 0)
	{
		if (access(pipex->cmd->args[0], F_OK) != 0)
		{
			ft_fprintf(STDERR_FILENO, "Fraudistan: %s: ", pipex->cmd->args[0]);
			perror("");
			exit(127);
		}
		if (access(pipex->cmd->args[0], X_OK != 0) != 0)
		{
			ft_fprintf(STDERR_FILENO, "Fraudistan: %s: ", pipex->cmd->args[0]);
			perror("");
			exit(EXIT_PERMISSION_DENIED);
		}
	}
}
