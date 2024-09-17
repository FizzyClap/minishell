#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	struct s_lexer	*redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			**tab_env;
	char			*line;
	char			*var;
	char			*args;
	int				token;
	struct s_env	*next;
}	t_env;

typedef struct s_quote
{
	bool			d_quote;
	bool			quote;
}	t_quote;

typedef struct s_var
{
	char			*variable;
	bool			exist;
	struct s_var	*next;
}	t_var;

typedef struct s_split_cmd
{
	struct s_lexer		*cmd;
	struct s_split_cmd	*next;
}	t_split_cmd;

typedef struct s_lexer
{
	char			*element;
	int				token;
	int				index;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_pipex
{
	int			infile;
	char		*infile_error;
	bool		infile_exist;
	int			outfile;
	char		*outfile_error;
	int			i;
	int			nb_pipes;
	int			status;
	int			**pipefd;
	char		*limiter;
	t_lexer		*last_infile;
	pid_t		*child;
	t_env		*env;
	t_cmd		*cmd;
}	t_pipex;

#endif
