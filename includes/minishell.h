/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 09:45:36 by roespici          #+#    #+#             */
/*   Updated: 2024/09/09 08:34:06 by roespici         ###   ########.fr       */
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

//INIT
void		init_minishell(t_env **env);
void		init_pipex(t_pipex *pipex, t_cmd *command, t_env *env);
//BUILTINS/BUILTINS ENV
void		builtin_env(t_env *head, char *command);
void		builtin_export(t_env *env, char *cmd, char **args);
void		builtin_unset(t_env *env, char **args);
//BUILTINS/BUILTINS OTHER
void		builtin_echo(t_cmd *command);
void		builtin_cd(t_env *env, char **args);
void		builtin_pwd(char **args);
void		builtin_exit(t_env *env, t_cmd *command);
//BUILTINS/CHAIN LIST UTILS
t_env		*create_node(char *env_line);
void		modify_node(t_env *env, char *env_line);
void		add_node(t_env **head, char *env_line);
void		swap_nodes(t_env *node1, t_env *node2);
//BUILTINS/UTILS BUILTINS
int			is_builtins(t_cmd *command);
void		sort_env(t_env *env);
t_env		*copy_env(t_env *env);
void		free_env(t_env *head);
//LEXER/LEXER LST
t_lexer		*lexer_new(char *element, int token);
void		lexer_add_back(t_lexer **lst, t_lexer *new);
//LEXER/LEXER REDIR
t_lexer		*clean_redir(t_lexer *lexer);
//LEXER/LEXER
t_lexer		*make_lexer(char *input);
//PARSER/PARSER LST
t_cmd		*cmd_new(char *line, char *cmd, char **args, t_lexer *out);
void		cmd_add_back(t_cmd **lst, t_cmd *new);
//PARSER/PARSER
t_cmd		*make_cmd(t_split_cmd *split);
//PARSER/SPLIT CMD
t_split_cmd	*split_cmd(t_lexer *lexer);
//PIPEX/PATH BUILDING
char		*get_path(t_pipex *pipex);
void		tab_env(t_env *env);
//PIPEX/PIPEX
void		execute_pipes(t_pipex *pipex);
void		exec_command(t_pipex *pipex);
void		exec(t_pipex *pipex, int inputfd, int outputfd);
void		execute_pipex (t_cmd *command, t_env *env);
//PIPEX/UTILS PIPEX
void		error_exit(const char *msg);
int			open_infile(t_pipex *pipex);
int			open_outfile(t_pipex *pipex);
void		close_pipes(t_pipex *pipex);
int			open_and_exec(t_pipex *pipex);
void		free_pipex(t_pipex *pipex);
void		execute_builtins(t_env *env, t_cmd *command);

#endif
