/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:10:30 by roespici          #+#    #+#             */
/*   Updated: 2024/08/18 14:15:32 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	strlen_gnl(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i])
		i++;
	return (i);
}

void	strcpy_gnl(char *dest, const char *src)
{
	int	i;

	i = -1;
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
}

char	*strdup_gnl(const char *s)
{
	char	*dest;

	if (!s)
		return (NULL);
	dest = malloc(sizeof(char) * (strlen_gnl((char *)s) + 1));
	if (!dest)
		return (NULL);
	strcpy_gnl(dest, s);
	return (dest);
}

char	*strchr_gnl(const char *s, int c)
{
	int	i;

	i = 0;
	c = (unsigned char)c;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return ((char *)s + i);
	return (NULL);
}

char	*strjoin_gnl(char *s1, const char *s2)
{
	char	*dest;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = strlen_gnl(s1);
	s2_len = strlen_gnl(s2);
	if (!s1 && !s2)
		return (strdup_gnl(""));
	if (!s1)
		return (strdup_gnl(s2));
	if (!s2)
		return (strdup_gnl(s1));
	dest = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!dest)
		return (NULL);
	strcpy_gnl(dest, s1);
	strcpy_gnl(dest + s1_len, s2);
	free(s1);
	return (dest);
}
