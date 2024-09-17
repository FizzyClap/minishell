/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:05:56 by roespici          #+#    #+#             */
/*   Updated: 2024/09/17 14:05:57 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

extern int	g_exit_code;

# define PROMPT "Fraudistan> "
# define SUCCESS 0
# define FAILURE -1
# define ISBUILTINS 1
# define ISNOTBUILTINS 0
//TOKEN
# define WORD 0
# define PIPE 1
# define IN 2
# define OUT 3
# define HEREDOC 4
# define APPEND 5
# define OR 6
# define AND 7
# define CONNARD 8
//ERROR MESSAGES
# define ERR_SYNT "Fraudistan: syntax error near unexpected token"
# define EXIT_SYNTAX_ERROR 2
# define EXIT_PERMISSION_DENIED 126
# define COMMAND_NOT_FOUND 127
# define EXIT_SIGINT 130

#endif
