/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 09:45:36 by roespici          #+#    #+#             */
/*   Updated: 2024/09/05 11:41:47 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include "structs.h"
# include "define.h"
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
# include <stdbool.h>

//PIPEX/EXEC
int		execute_pipex(int argc, char **argv, char *const *envp);
//PIPEX/FREE
void	free_pipex(t_pipex *pipex);
void	free_split(char **split);
//PIPEX/HERE_DOC
void	here_doc(t_pipex *pipex, char *limiter, int argc, char **argv);
//PIPEX/PATH BUILDING
char	*get_path(t_pipex *pipex, char *command);
//PIPEX/PIPEX
void	execute_pipes(t_pipex *pipex, char **argv, int start);
//PIPEX/UTILS PIPEX
void	error_exit(const char *msg);
int		open_infile(t_pipex *pipex, char **argv);
int		open_outfile(t_pipex *pipex, int argc, char **argv);
void	close_pipes(t_pipex *pipex);
void	init_pipex(t_pipex *pipex, int argc, char **argv, char *const *envp);
//BUILTINS/BUILTINS ENV
void	builtin_env(t_env *head, char *command);
void	builtin_export(t_env *env, char **args);
void	builtin_unset(t_env *env, char **args);
//BUILTINS/BUILTINS OTHER
void	builtin_echo(char **args);
void	builtin_cd(char **args);
void	builtin_pwd(void);
void	builtin_exit(t_env *env, char **args);
//BUILTINS/CHAIN LIST UTILS
t_env	*create_node(char *env_line);
void	modify_node(t_env *env, char *env_line);
void	add_node(t_env **head, char *env_line);
void	swap_nodes(t_env *node1, t_env *node2);
//BUILTINS/UTILS BUILTINS
int		is_builtins(char *command);
void	init_env(t_env **env);
void	sort_env(t_env *env);
t_env	*copy_env(t_env *env);
void	free_env(t_env *head);
int		count_args(char **args);

#endif
