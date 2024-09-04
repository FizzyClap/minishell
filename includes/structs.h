/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:48:07 by roespici          #+#    #+#             */
/*   Updated: 2024/09/04 11:16:30 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_command
{
	char				*line;
	char				*cmd;
	char				**args;
	char				**env;
	char				*input_redirection;
	char				*output_redirection;
	struct s_command	*next;
}	t_command;

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
	char *const	*envp;
	int			infile_open;
	int			outfile_open;
	char		*limiter;
	pid_t		*child;
}	t_pipex;

#endif
