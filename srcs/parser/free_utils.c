/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoy <ggoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:38:31 by gartan            #+#    #+#             */
/*   Updated: 2024/09/13 10:36:12 by ggoy             ###   ########.fr       */
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

	tmp = NULL;
	while (tmp)
	{
		tmp = cmd->next;
		free(tmp->cmd);
		ft_free_tab(tmp->args);
		free_lexer(tmp->redir);
		free(cmd);
		cmd = tmp;
	}
}

void	free_vars(t_var *var)
{
	t_var	*tmp;

	while (var)
	{
		tmp = var->next;
		if (var->variable)
			free(var->variable);
		free(var);
		var = tmp;
	}
}
