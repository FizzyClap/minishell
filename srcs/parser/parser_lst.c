/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoy <ggoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/09/14 18:13:20 by ggoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

t_cmd	*cmd_new(char *cmd, char **args, t_lexer *out)
{
	t_cmd	*tcmd;

	tcmd = malloc(sizeof(t_cmd));
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

//void	make_lines(t_lexer *lexer, t_cmd **final)
//{
//	t_cmd	*tmp;
//	t_lexer	*temp;

//	temp = lexer;
//	tmp = *final;
//	while (temp)
//	{
//		if (temp && temp->element && temp->token != PIPE)
//		{
//			if (tmp->line == NULL)
//				tmp->line = ft_strdup(temp->element);
//			else
//				tmp->line = ft_strjoin(tmp->line, temp->element);
//			tmp->line = ft_strjoin(tmp->line, " ");
//			temp = temp->next;
//		}
//		else if (temp && temp->element && temp->token == PIPE)
//		{
//			temp = temp->next;
//			tmp = tmp->next;
//		}
//	}
//}
