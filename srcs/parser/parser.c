/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:40:58 by roespici          #+#    #+#             */
/*   Updated: 2024/09/09 18:00:39 by roespici         ###   ########.fr       */
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
}

static int	trim_args(t_split_cmd **split, t_cmd **new, int arg)
{
	if ((*new)->args == NULL)
		(*new)->args = ft_calloc(count_args((*split)->cmd) + 1, sizeof(char *));
	(*new)->args[++arg] = ft_strdup((*split)->cmd->element);
	(*split)->cmd = (*split)->cmd->next;
	return (arg);

}

void	cmd_node(t_split_cmd *split, int arg, t_cmd **new)
{
	t_lexer *ntm;

	ntm = split->cmd;
	while (split->cmd)
	{
		if (split->cmd->token == WORD && (*new)->cmd == NULL)
			title_cmd(&split, new);
		else if (split->cmd->token == WORD)
			arg = trim_args(&split, new, arg);
		else
		{
			lexer_add_back(&(*new)->redir, lexer_new(ft_strdup(split->cmd->element), split->cmd->token));
			split->cmd = split->cmd->next;
		}
	}
	split->cmd = ntm;
}

t_cmd	*make_cmd(t_split_cmd *split)
{
	t_cmd		*final;
	t_cmd		*new;

	final = NULL;
	while (split)
	{
		new = cmd_new(NULL, NULL, NULL, NULL);
		cmd_node(split, -1, &new);
		split = split->next;
		cmd_add_back(&final, new);
	}
	return (final);
}
