/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:56:05 by roespici          #+#    #+#             */
/*   Updated: 2024/09/12 09:58:25 by roespici         ###   ########.fr       */
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

static void	exec_here_doc(t_pipex *pipex)
{
	if (pipex->cmd->redir->next)
	{
		find_last_redir(pipex->cmd, IN);
		open_infile(pipex);
	}
	else
		pipex->infile = open("here_doc.tmp", O_RDONLY);

	execute_pipes(pipex);
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
		else if (redir->token == token)
			last = redir;
		redir = redir->next;
	}
	printf("last = %s\n", last->element);
	return (last);
}

void	here_doc(t_pipex *pipex)
{
	t_lexer	*last;

	last = find_last_redir(pipex->cmd, HEREDOC);
	last = find_last_redir(pipex->cmd, OUT);
	last = find_last_redir(pipex->cmd, APPEND);
	last = find_last_redir(pipex->cmd, IN);
	if (!last)
		return ;
	pipex->limiter = ft_strdup(pipex->cmd->redir->element);
	fill_here_doc(pipex);
	if (pipex->cmd->redir->next && pipex->cmd->redir != last)
	{
		pipex->cmd->redir = pipex->cmd->redir->next;
		free(pipex->limiter);
		unlink("here_doc.tmp");
		open_infile(pipex);
	}
	if (open_outfile(pipex) == FAILURE)
	{
		printf("bash: %s: Permission denied\n", last->element);
		free(pipex->limiter);
		unlink("here_doc.tmp");
		return ;
	}
	if (pipex->cmd->cmd && pipex->cmd->redir == last)
	{
		exec_here_doc(pipex);
		close_pipes(pipex);
		unlink("here_doc.tmp");
	}
}
