/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoy <ggoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 09:20:52 by ggoy              #+#    #+#             */
/*   Updated: 2024/09/13 10:34:59 by ggoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("tab[%i] = %s\n", i, tab[i]);
		i++;
	}
}

void	print_lexer(t_lexer *lexer)
{
	t_lexer	*tmp;
	int		i;

	i = 0;
	tmp = lexer;
	while (tmp)
	{
		printf("lexer nbr: %i\n", i);
		printf("element: %s\ntoken: %i\n", tmp->element, tmp->token);
		i++;
		tmp = tmp->next;
	}
}

void	print_split(t_split_cmd *split)
{
	t_split_cmd	*tmp;
	int			i;

	tmp = split;
	i = 0;
	while (tmp)
	{
		printf("split nbr: %i\n", i);
		print_lexer(tmp->cmd);
		printf("\n");
		i++;
		tmp = tmp->next;
	}
}

void	print_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmd;
	i = 0;
	while (tmp)
	{
		printf("cmd nbr: %i\n", i);
		printf("line: %s\ncmd: %s\n", tmp->line, tmp->cmd);
		printf("args:\n");
		print_tab(tmp->args);
		printf("redir:\n");
		print_lexer(tmp->redir);
		printf("\n");
		i++;
		tmp = tmp->next;
	}
}

void	print_vars(t_var *var)
{
	t_var	*tmp;
	int		i;

	i = 0;
	tmp = var;
	while (tmp)
	{
		printf("variable %i:\n", i);
		printf("var: %s\nTrue?: %i\n", tmp->variable, tmp->exist);
		printf("\n");
		i++;
		tmp = tmp->next;
	}
}
