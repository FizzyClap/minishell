/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:10:36 by roespici          #+#    #+#             */
/*   Updated: 2024/08/20 10:41:13 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

char	*get_next_line(int fd);
size_t	strlen_gnl(const char *str);
char	*strdup_gnl(const char *s);
char	*strchr_gnl(const char *s, int c);
char	*strjoin_gnl(char *s1, const char *s2);
void	strcpy_gnl(char *dest, const char *src);

#endif
