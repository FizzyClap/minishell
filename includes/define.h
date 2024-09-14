/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoy <ggoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:23:28 by roespici          #+#    #+#             */
/*   Updated: 2024/09/14 16:26:33 by ggoy             ###   ########.fr       */
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
# define COMMAND_NOT_FOUND 127
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
# define ERR_SYNT "Frausdistan: syntax error near unexpected token"

#endif