#include "../../includes/minishell.h"

t_lexer	*lexer_new(char *element, int token)
{
	t_lexer	*tlex;

	tlex = malloc(sizeof(t_lexer));
	tlex->element = element;
	tlex->token = token;
	tlex->next = NULL;
	return (tlex);
}

static t_lexer	*lexer_last(t_lexer *lst)
{
	if (!lst)
		return (NULL);
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	lexer_add_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*last_element;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last_element = lexer_last(*lst);
	last_element->next = new;
}

int	list_cmd_size(t_cmd *lst)
{
	int	count;

	count = 0;
	if (!lst)
		return (count);
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
