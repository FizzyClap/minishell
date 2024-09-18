/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:06:02 by roespici          #+#    #+#             */
/*   Updated: 2024/09/18 11:49:34 by roespici         ###   ########.fr       */
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

//BUILTINS/BUILTINS_CD
void		builtin_cd(t_env *env, char **args, int fd);
//BUILTINS/BUILTINS_ENV
void		builtin_export(t_env *env, t_cmd *cmd, int fd);
void		builtin_env(t_env *head, t_cmd *cmd, int fd);
//BUILTINS/BUILTINS_OTHER
void		builtin_echo(t_cmd *command, int fd);
void		builtin_pwd(t_env *env, int fd);
void		builtin_exit(t_env *env, t_cmd *command);
void		builtin_unset(t_env *env, char **args);
//BUILTINS/CHAIN_LIST_UTILS
t_env		*create_node(char *env_line);
void		add_node(t_env **head, char *env_line);
void		modify_node(t_env *env, char *env_line);
void		swap_nodes(t_env *node1, t_env *node2);
//BUILTINS/UTILS_BUILTINS
int			is_builtins(t_cmd *command);
void		execute_builtins(t_pipex *pipex);
//BUILTINS/UTILS_ENV
t_env		*copy_env(t_env *env);
void		free_env(t_env *head);
char		*get_env(t_env *env, char *var_name);
void		sort_env(t_env *env);
//DEBUG/PRINT
void		print_tab(char **tab);
void		print_lexer(t_lexer *lexer);
void		print_split(t_split_cmd *split);
void		print_cmd(t_cmd *cmd);
//LEXER/LEXER_LST
t_lexer		*lexer_new(char *element, int token, int index);
void		lexer_add_back(t_lexer **lst, t_lexer *new);
//LEXER/LEXER_REDIR
t_lexer		*clean_redir(t_lexer *lexer);
int			is_token(char c);
int			next_token(char *input, int start, int i);
//LEXER/LEXER_UTILS
bool		change_bool(bool quote, t_lexer *new);
int			check_valid_token(char c, int i);
int			next_token_pr(char *input, int start);
int			lexer_len(char *input, int start);
int			is_space(char c);
//LEXER/LEXER
t_lexer		*make_lexer(char *input);
//LEXER/PROMPT_LOOP
t_cmd		*prompt_loop(char *line);
//PARSER/FREE_UTILS
void		free_lexer(t_lexer *lexer);
void		free_split_cmd(t_split_cmd *split);
void		free_cmd(t_cmd *cmd);
void		free_vars(t_var *var);
//PARSER/PARSER_LST
t_cmd		*cmd_new(char *cmd, char **args, t_lexer *out);
void		cmd_add_back(t_cmd **lst, t_cmd *new);
int			list_cmd_size(t_cmd *lst);
//PARSER/PARSER
t_cmd		*make_cmd(t_split_cmd *split);
//PARSER/SPLIT_CMD
t_split_cmd	*split_cmd(t_lexer *lexer);
//PIPEX/EXECUTION
void		execute_pipeline(t_cmd *command, t_env *env);
void		execute_pipes(t_pipex *pipex);
//PIPEX/HERE DOC
void		here_doc(t_pipex *pipex, t_lexer *redir);
//PIPEX/INIT
void		init_env(t_env **env, char *const *envp);
void		init_pipex(t_pipex *pipex, t_cmd *command, t_env *env);
//PIPEX/OPEN FILES
void		open_files(t_pipex *pipex);
void		open_infile(t_pipex *pipex);
int			open_outfile(t_pipex *pipex);
//PIPEX/PATH BUILDING
void		exec_command(t_pipex *pipex);
//PIPEX/TAB ENV
void		create_tab_env(t_env *env);
//PIPEX/UTILS FILES
int			files_are_valid(t_pipex *pipex, bool should_exit);
int			create_outfile(t_pipex *pipex, t_lexer *parse);
void		verif_is_executable(t_pipex *pipex);
//PIPEX/UTILS PIPEX
void		error_exit(const char *msg);
pid_t		fork_child(void);
void		close_pipes(t_pipex *pipex);
void		free_pipex(t_pipex *pipex);
t_lexer		*find_last_redir(t_cmd *cmd, int token);
//SIGNALS/SIGNALS
void		signals(void);
void		ctrl_d(char *line);
void		here_signals(void);
//VAR_ENV/PARSING_ENV_UTILS
t_quote		strct_bool_change(t_quote quote, char c);
int			check_chr(char *line, int i);
int			progress(char *line, int i);
char		*dup_tmp(char *line, int dup, int i, int start);
t_var		*var_exceptions(t_var *new, char *line, int i);
//VAR_ENV/PARSING_ENV
char		*parsing_env(char *line, t_env *env);
//VAR_ENV/VAR_ENV_LST
t_var		*var_new(char *variable, bool exist);
void		var_add_back(t_var **lst, t_var *new);
int			list_var_size(t_cmd *lst);

#endif
