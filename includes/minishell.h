/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 09:45:36 by roespici          #+#    #+#             */
/*   Updated: 2024/09/02 07:59:11 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include "structs.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SUCCESS 0
# define FAILURE -1

//FONCTIONS EXEC
int		execute_pipex(int argc, char **argv, char *const *envp);
void	here_doc(t_pipex *pipex, char const *limiter, int argc, char **argv);
pid_t	fork_child(void);
void	exec(t_pipex *pipex, int inputfd, int outputfd, char *cmd);
void	execute_pipes(t_pipex *pipex, char **argv, int start);
void	error_exit(const char *msg);
//FONCTIONS PATH BUILDING
char	*get_path(t_pipex *pipex, const char *command);
//FONCTIONS UTILS
void	init_pipex(t_pipex *pipex, int argc, char **argv, char *const *envp);
int		open_infile(t_pipex *pipex, char **argv);
int		open_outfile(t_pipex *pipex, int argc, char **argv);
void	close_pipes(t_pipex *pipex);
//FONCTIONS FREE
void	free_split(char **split);
void	free_pipex(t_pipex *pipex);

#endif
