/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/09/13 20:28:36 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

static void	fill_here_doc(t_pipex *pipex)
{
	char	*line;

	pipex->infile = open("here_doc.tmp", O_CREAT | O_WRONLY, 0644);
	if (pipex->infile < 0)
		error_exit("Here_doc error");
	while (1)
	{
		ft_putstr("> ");
		line = get_next_line(STDIN_FILENO);
		if (ft_strcmp(line, pipex->limiter) == 10)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, pipex->infile);
		free(line);
	}
	close(pipex->infile);
}

static int	exec_here_doc(t_pipex *pipex, t_lexer *last_heredoc)
{
	if (ft_strcmp(pipex->last_infile->element, last_heredoc->element) == 0)
		pipex->infile = open("here_doc.tmp", O_RDONLY);
	else
	{
		free(pipex->limiter);
		unlink("here_doc.tmp");
		return (FAILURE);
	}
	execute_pipes(pipex);
	return (SUCCESS);
}

t_lexer	*find_last_redir(t_cmd *cmd, int token)
{
	t_lexer	*last;
	t_lexer	*redir;

	last = NULL;
	redir = cmd->redir;
	while (redir)
	{
		if (token == OUT || token == APPEND)
		{
			if (redir->token == OUT || redir->token == APPEND)
				last = redir;
		}
		else if (token == IN)
		{
			if (redir->token == IN || redir->token == HEREDOC)
				last = redir;
		}
		else if (token == HEREDOC)
			if (redir->token == token)
				last = redir;
		redir = redir->next;
	}
	return (last);
}

void	here_doc(t_pipex *pipex, t_lexer *redir)
{
	t_lexer	*last;
	
	last = find_last_redir(pipex->cmd, HEREDOC);
	pipex->limiter = ft_strdup(redir->element);
	fill_here_doc(pipex);
	if (redir != last)
	{
		free(pipex->limiter);
		unlink("here_doc.tmp");
		return ;
	}
	if (open_outfile(pipex) == FAILURE)
	{
		free(pipex->limiter);
		unlink("here_doc.tmp");
		return ;
	}
	if (exec_here_doc(pipex, last) == FAILURE)
		return ;
	close_pipes(pipex);
	free(pipex->limiter);
	unlink("here_doc.tmp");
}
