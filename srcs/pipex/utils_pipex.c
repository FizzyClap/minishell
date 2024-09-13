/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoy <ggoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/09/13 10:04:19 by ggoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

void	error_exit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int	open_infile(t_pipex *pipex)
{
	t_lexer	*parse;

	parse = pipex->cmd->redir;
	pipex->last_infile = find_last_redir(pipex->cmd, IN);
	if (!pipex->last_infile)
	{
		pipex->infile = STDIN_FILENO;
		return (SUCCESS);
	}
	while (parse)
	{
		if (parse->token == HEREDOC)
			here_doc(pipex, parse);
		if (parse->token == IN)
		{
			pipex->infile = open(parse->element, O_RDONLY);
			if (pipex->infile == FAILURE)
			{
				ft_fprintf(STDERR_FILENO, "bash: %s: ", parse->element);
				perror("");
				pipex->infile = STDIN_FILENO;
				return (FAILURE);
			}
			if (ft_strcmp(parse->element, pipex->last_infile->element) == 0)
				return (SUCCESS);
			close(pipex->infile);
		}
		parse = parse->next;
	}
	return (SUCCESS);
}

int	open_outfile(t_pipex *pipex)
{
	t_lexer	*parse;
	t_lexer	*last;

	parse = pipex->cmd->redir;
	last = find_last_redir(pipex->cmd, OUT);
	if (!last)
	{
		pipex->outfile = STDOUT_FILENO;
		return (SUCCESS);
	}
	while (parse)
	{
		if (parse->token == OUT || parse->token == APPEND)
		{
			if (parse->token == OUT)
				pipex->outfile = open(parse->element, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (parse->token == APPEND)
				pipex->outfile = open(parse->element, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (access(parse->element, W_OK) == FAILURE)
			{
				if (pipex->print_msg == false)
					ft_fprintf(STDERR_FILENO, "bash: %s: Permission denied\n", \
						parse->element);
				pipex->print_msg = true;
				pipex->outfile = STDOUT_FILENO;
				return (FAILURE);
			}
			if (ft_strcmp(parse->element, last->element) == 0)
				return (SUCCESS);
			close(pipex->outfile);
		}
		parse = parse->next;
	}
	return (SUCCESS);
}

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->nb_pipes)
	{
		close(pipex->pipefd[i][0]);
		close(pipex->pipefd[i][1]);
	}
}

void	free_pipex(t_pipex *pipex)
{
	int	i;

	if (pipex->nb_pipes > 0)
		close_pipes(pipex);
	i = -1;
	if (pipex->nb_pipes)
	{
		while (++i < pipex->nb_pipes)
		{
			free(pipex->pipefd[i]);
			pipex->pipefd[i] = NULL;
		}
	}
	free(pipex->pipefd);
	free(pipex->child);
	free(pipex);
}
