/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartan <gartan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:23:28 by roespici          #+#    #+#             */
/*   Updated: 2024/09/09 17:22:09 by gartan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

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
//# define DOLLAR 6
# define QUESTION 7
# define OR 8
# define AND 9

#endif
