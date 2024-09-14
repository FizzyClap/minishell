/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoy <ggoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 09:45:36 by roespici          #+#    #+#             */
/*   Updated: 2024/09/14 11:58:06 by ggoy             ###   ########.fr       */
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
# include <signal.h>
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
# include <curses.h>

//MAIN
void		execute_builtins(t_env *env, t_cmd *command, int fd);
//INIT
void		init_env(t_env **env);
void		init_pipex(t_pipex *pipex, t_cmd *command, t_env *env);
//BUILTINS/BUILTINS CD
void		builtin_cd(t_env *env, char **args, int fd);
//BUILTINS/BUILTINS ENV
void		builtin_export(t_env *env, t_cmd *cmd, int fd);
void		builtin_unset(t_env *env, char **args);
void		builtin_env(t_env *head, char *command, int fd);
//BUILTINS/BUILTINS OTHER
void		builtin_echo(t_cmd *command, int fd);
void		builtin_pwd(t_env *env, char **args, int fd);
void		builtin_exit(t_env *env, t_cmd *command);
//BUILTINS/CHAIN LIST UTILS
t_env		*create_node(char *env_line);
void		add_node(t_env **head, char *env_line);
void		modify_node(t_env *env, char *env_line);
void		swap_nodes(t_env *node1, t_env *node2);
//BUILTINS/UTILS BUILTINS
int			is_builtins(t_cmd *command);
t_env		*copy_env(t_env *env);
void		free_env(t_env *head);
char		*get_env(t_env *env, char *var_name);
//LEXER/LEXER LST
t_lexer		*lexer_new(char *element, int token);
void		lexer_add_back(t_lexer **lst, t_lexer *new);
int			list_cmd_size(t_cmd *lst);
//VAR_ENV/VAR_ENV_LST
char		*parsing_env(char *line, t_env *env);
t_var		*var_new(char *variable, bool exist);
void		var_add_back(t_var **lst, t_var *new);
int			list_var_size(t_cmd *lst);
//LEXER/LEXER REDIR
t_lexer		*clean_redir(t_lexer *lexer);
//LEXER/LEXER
t_lexer		*make_lexer(char *input);
int			check_valid_lex(t_lexer *lexer);
//PARSER/PARSER LST
t_cmd		*cmd_new(char *line, char *cmd, char **args, t_lexer *out);
void		cmd_add_back(t_cmd **lst, t_cmd *new);
//PARSER/PARSER
t_cmd		*make_cmd(t_split_cmd *split);
void		make_lines(t_lexer *lexer, t_cmd **final);
//PARSER/SPLIT CMD
t_split_cmd	*split_cmd(t_lexer *lexer);
//PIPEX/EXECUTION
void		execute_pipeline(t_cmd *command, t_env *env);
void		execute_pipes(t_pipex *pipex);
//PIPEX/HERE DOC
void		here_doc(t_pipex *pipex, t_lexer *redir);
//PIPEX/OPEN FILES
void		open_files(t_pipex *pipex);
void		open_infile(t_pipex *pipex);
int			open_outfile(t_pipex *pipex);
//PIPEX/PATH BUILDING
void		exec_command(t_pipex *pipex);
//PIPEX/UTILS PIPEX
void		error_exit(const char *msg);
pid_t		fork_child(void);
void		close_pipes(t_pipex *pipex);
void		free_pipex(t_pipex *pipex);
t_lexer		*find_last_redir(t_cmd *cmd, int token);
//FREE_UTILS
void		free_cmd(t_cmd *cmd);
void		free_split_cmd(t_split_cmd *split);
void		free_lexer(t_lexer *lexer);
void		free_vars(t_var *var);
//SIGNALS
void		set_termios(bool set);
void		ft_ctrl_c(int signum);
void		ft_ctrl_bs(int signum);
void		ft_ctrld(char *line);
//DEBUG
void		print_tab(char **tab);
void		print_lexer(t_lexer *lexer);
void		print_split(t_split_cmd *split);
void		print_cmd(t_cmd *cmd);
//VAR_ENV/VAR_ENV_LST
char		*parsing_env(char *line, t_env *env);
t_var		*var_new(char *variable, bool exist);
void		var_add_back(t_var **lst, t_var *new);
int			list_var_size(t_cmd *lst);
void		print_vars(t_var *var);

#endif
