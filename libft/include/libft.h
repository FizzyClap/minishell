/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:02:12 by roespici          #+#    #+#             */
/*   Updated: 2024/09/02 08:08:40 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../gnl/get_next_line.h"
# include "../printf/printf.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_atoi(char *nptr);
char				*ft_itoa(int nb);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
char				*ft_strchr(char *s, int c);
char				*ft_strdup(char *s);
size_t				ft_strlcat(char *dst, char *src, size_t size);
size_t				ft_strlcpy(char *dst, char *src, size_t size);
size_t				ft_strlen(char *str);
int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(char *s1, char *s2, size_t n);
char				*ft_strnstr(char *big, char *little,
						size_t len);
char				*ft_strrchr(char *s, int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
char				*ft_strmapi(char *s, char (*f)(unsigned int, char));
void				ft_putendl_fd(char *s, int fd);
char				**ft_split(char *s, char c);
char				*ft_substr(char *s, unsigned int start, size_t len);
char				*ft_strmapi(char *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strtrim(char *s1, char *set);
char				*ft_strjoin(char *s1, char *s2);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);

#endif
