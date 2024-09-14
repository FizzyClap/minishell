/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:09:01 by roespici          #+#    #+#             */
/*   Updated: 2024/09/14 11:05:17 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	return_infile(t_pipex *pipex, t_lexer *parse);
static int	return_outfile(t_pipex *pipex, t_lexer *parse, t_lexer *last);

void	open_files(t_pipex *pipex)
{
	open_infile(pipex);
	open_outfile(pipex);
}

void	open_infile(t_pipex *pipex)
{
	t_lexer	*parse;

	parse = pipex->cmd->redir;
	pipex->last_infile = find_last_redir(pipex->cmd, IN);
	if (!pipex->last_infile)
	{
		pipex->infile = STDIN_FILENO;
		return ;
	}
	return_infile(pipex, parse);
	return ;
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
	if (return_outfile(pipex, parse, last) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static void	return_infile(t_pipex *pipex, t_lexer *parse)
{
	while (parse)
	{
		if (parse->token == HEREDOC)
			here_doc(pipex, parse);
		if (parse->token == IN)
		{
			pipex->infile = open(parse->element, O_RDONLY);
			if (pipex->infile == FAILURE)
			{
				pipex->infile_error = parse->element;
				pipex->infile_exist = false;
			}
			if (ft_strcmp(parse->element, pipex->last_infile->element) == 0)
				return ;
			close(pipex->infile);
		}
		parse = parse->next;
	}
	return ;
}

static int	return_outfile(t_pipex *pipex, t_lexer *parse, t_lexer *last)
{
	while (parse)
	{
		if (parse->token == OUT || parse->token == APPEND)
		{
			if (parse->token == OUT)
				pipex->outfile = open(parse->element, \
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (parse->token == APPEND)
				pipex->outfile = open(parse->element, \
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (access(parse->element, W_OK) == FAILURE)
			{
				pipex->outfile_error = parse->element;
				pipex->outfile = FAILURE;
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
