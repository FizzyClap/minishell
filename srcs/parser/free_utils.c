/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartan <gartan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:38:31 by gartan            #+#    #+#             */
/*   Updated: 2024/09/07 17:12:59 by gartan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_lexer(t_lexer *lexer)
{
	t_lexer	*tmp;

	tmp = lexer;
	while (tmp)
	{
		free(tmp->element);
		tmp = tmp->next;
	}
	free(lexer);
}

void	free_split_cmd(t_split_cmd *split)
{
	t_split_cmd	*tmp;

	tmp = split;
	while (tmp)
	{
		free_lexer(tmp->cmd);
		tmp = tmp->next;
	}
	free(split);
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		free(tmp->line);
		free(tmp->cmd);
		ft_free_tab(tmp->args);
		free_lexer(tmp->redir);
		tmp = tmp->next;
	}
	free(cmd);
}