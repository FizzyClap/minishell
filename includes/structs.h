/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:48:07 by roespici          #+#    #+#             */
/*   Updated: 2024/09/02 07:36:34 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_command
{
	char				*cmd;
	char				**args;
	char				*input_redirection;
	char				*output_redirection;
	struct s_command	*next;
}	t_command;

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
	const char	*limiter;
	pid_t		*child;
}	t_pipex;

#endif
