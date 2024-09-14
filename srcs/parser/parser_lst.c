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
