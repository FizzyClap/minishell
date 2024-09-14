#include "../../includes/minishell.h"

static void	long_line(t_lexer *clean, char *itoa)
{
	printf("syntax error near unexpected token `newline'\n");
	free_lexer(clean);
	free(itoa);
}

t_lexer	*clean_redir(t_lexer *lexer)
{
	t_lexer	*clean;
	char	*itoa;

	clean = NULL;
	while (lexer)
	{
		itoa = ft_itoa(lexer->token);
		if (ft_chrinstr("2345", itoa[0]) == 0)
		{
			if (!lexer->next)
				return (long_line(clean, itoa), NULL);
			lexer_add_back(&clean, \
				lexer_new(ft_strdup(lexer->next->element), lexer->token));
			lexer = lexer->next->next;
		}
		else
		{
			lexer_add_back(&clean, \
				lexer_new(ft_strdup(lexer->element), lexer->token));
			lexer = lexer->next;
		}
		free(itoa);
	}
	return (clean);
}

int	check_valid_lex(t_lexer *lexer)
{
	t_lexer	*tmp;

	tmp = lexer;
	while (tmp)
	{
		if (tmp->next && tmp->token == PIPE && tmp->next->token == PIPE)
		{
			printf("%s `%s'\n", ERR_SYNT, tmp->next->element);
			return (0);
		}
		else if (tmp->next && tmp->token > WORD && tmp->next->token > WORD)
		{
			printf("%s `%s'\n", ERR_SYNT, tmp->next->element);
			return (0);
		}
		else if (!tmp->next && tmp->token > WORD && tmp->token < 7)
		{
			printf("%s%s", ERR_SYNT, " `newline'\n");
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
