/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:48:07 by roespici          #+#    #+#             */
/*   Updated: 2024/09/06 09:12:06 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_cmd
{
	char			*line;
	char			*cmd;
	char			**args;
	int				exit_code;
	struct s_lexer	*output_redirection;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*line;
	char			*var;
	char			*args;
	int				token;
	struct s_env	*next;
}	t_env;

typedef struct s_pipex
{
	int			infile;
	int			outfile;
	int			i;
	int			nb_pipes;
	int			status;
	int			exit_status;
	int			**pipefd;
	int			infile_open;
	int			infile_exist;
	int			outfile_open;
	char		*limiter;
	pid_t		*child;
	t_env		*env;
}	t_pipex;

typedef struct s_split_cmd
{
	struct s_lexer		*cmd;
	struct s_split_cmd	*next;
}	t_split_cmd;

typedef struct s_lexer
{
	char			*element;
	int				token;
	struct s_lexer	*next;
}	t_lexer;

#endif
