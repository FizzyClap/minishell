/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartan <gartan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:40:58 by roespici          #+#    #+#             */
/*   Updated: 2024/09/07 17:24:00 by gartan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_args(t_lexer *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		if (cmd->token == WORD)
			i++;
		cmd = cmd->next;
	}
	return (i);
}

static void	title_cmd(t_split_cmd **split, t_cmd **new)
{
	(*new)->cmd = ft_strdup((*split)->cmd->element);
	(*new)->exit_code = 0;
}

static int	trim_args(t_split_cmd **split, t_cmd **new, int arg)
{
	if ((*new)->args == NULL)
		(*new)->args = ft_calloc(count_args((*split)->cmd) + 1, sizeof(char *));
	(*new)->args[++arg] = ft_strdup((*split)->cmd->element);
	(*split)->cmd = (*split)->cmd->next;
	return (arg);
	
}

void	cmd_node(t_split_cmd **split, int arg, t_cmd **new, t_lexer **new_lex)
{
	while ((*split)->cmd)
	{
		if ((*split)->cmd->token == WORD && (*new)->cmd == NULL)
			title_cmd(&(*split), new);
		else if ((*split)->cmd->token == WORD)
			arg = trim_args(&(*split), new, arg);
		else
		{
			(*new_lex) = lexer_new((*split)->cmd->element, (*split)->cmd->token);
			lexer_add_back(&(*new)->redir, *new_lex);
			(*split)->cmd = (*split)->cmd->next;
		}
	}
}

t_cmd	*make_cmd(t_split_cmd *split)
{
	t_cmd		*final;
	t_cmd		*new;
	t_lexer		*new_lex;
	int			arg;

	final = NULL;
	while (split)
	{
		new = cmd_new(NULL, NULL, NULL, NULL);
		arg = -1;
		cmd_node(&split, arg, &new, &new_lex);
		split = split->next;
		cmd_add_back(&final, new);
	}
	free_split_cmd(split);
	return (final);
}
