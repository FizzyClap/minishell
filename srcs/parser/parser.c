/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:40:58 by roespici          #+#    #+#             */
/*   Updated: 2024/09/06 09:51:04 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_args(t_lexer *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		if (cmd->token == 0)
			i++;
		cmd = cmd->next;
	}
	return (i);
}

t_cmd	*make_cmd(t_split_cmd *split)
{
	t_cmd	*final;
	t_cmd	*new;
	t_lexer	*tmp;
	int		arg;

	final = NULL;
	while (split)
	{
		new = cmd_new(NULL, NULL, NULL, NULL);
		if (split->cmd->token == 0)
		{
			new->cmd = ft_strdup(split->cmd->element);
			split->cmd = split->cmd->next;
		}
		arg = -1;
		new->args = ft_calloc(count_args(split->cmd) + 1, sizeof(char *));
		while (split->cmd)
		{
			if (split->cmd->token == 0)
			{
				new->args[++arg] = ft_strdup(split->cmd->element);
				split->cmd = split->cmd->next;
			}
			else
			{
				tmp = lexer_new(split->cmd->element, split->cmd->token);
				lexer_add_back(&new->output_redirection, tmp);
				split->cmd = split->cmd->next;
			}
		}
		cmd_add_back(&final, new);
		split = split->next;
	}
	return (final);
}
