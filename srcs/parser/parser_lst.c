/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartan <gartan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:41:51 by roespici          #+#    #+#             */
/*   Updated: 2024/09/07 17:50:12 by gartan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*cmd_new(char *line, char *cmd, char **args, t_lexer *out)
{
	t_cmd	*tcmd;

	tcmd = malloc(sizeof(t_cmd));
	tcmd->line = line;
	tcmd->cmd = cmd;
	tcmd->args = args;
	tcmd->redir = out;
	tcmd->next = NULL;
	return (tcmd);
}

static t_cmd	*cmd_last(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	cmd_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last_element;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last_element = cmd_last(*lst);
	last_element->next = new;
}

void	make_lines(t_lexer *lexer, t_cmd **final)
{
	t_cmd	*tmp;
	
	tmp = *final;
	while (lexer)
	{
		if (lexer->token != PIPE)
		{
			if (tmp->line == NULL)
				tmp->line = ft_strdup(lexer->element);
			else
				tmp->line = ft_strjoin(tmp->line, lexer->element);
			tmp->line = ft_strjoin(tmp->line, " ");
			lexer = lexer->next;
		}
		else if (lexer->token == PIPE)
		{
			lexer = lexer->next;
			tmp = tmp->next;
		}
	}
	// free_lexer(lexer);
}
