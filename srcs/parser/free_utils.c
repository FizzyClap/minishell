/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:38:31 by gartan            #+#    #+#             */
/*   Updated: 2024/09/11 16:36:11 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_lexer(t_lexer *lexer)
{
	t_lexer	*tmp;

	while (lexer)
	{
		tmp = lexer->next;
		free(lexer->element);
		free(lexer);
		lexer = tmp;
	}
}

void	free_split_cmd(t_split_cmd *split)
{
	t_split_cmd	*tmp;

	while (split)
	{
		tmp = split->next;
		free_lexer(split->cmd);
		free(split);
		split = tmp;
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		free(cmd->cmd);
		ft_free_tab(cmd->args);
		free_lexer(cmd->redir);
		free(cmd);
		cmd = tmp;
	}
}
