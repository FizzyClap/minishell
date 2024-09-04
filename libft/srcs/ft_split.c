/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 21:31:52 by roespici          #+#    #+#             */
/*   Updated: 2024/09/02 08:08:40 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_strlen_split(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

int	ft_countstrings(char *s, char c)
{
	size_t	i;
	size_t	strings;

	if (!s)
		return (0);
	i = 0;
	strings = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			strings++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (strings);
}

char	*ft_strdup_split(char *s, char c)
{
	size_t	i;
	char	*dest;
	size_t	wordlen;

	i = 0;
	wordlen = ft_strlen_split(s, c);
	dest = ft_calloc(sizeof(char), (wordlen + 1));
	if (!dest)
		return (NULL);
	while (i < wordlen)
	{
		dest[i] = s[i];
		i++;
	}
	return (dest);
}

char	**ft_split(char *s, char c)
{
	size_t		i;
	int			j;
	size_t		countstrings;
	char		**splits;

	if (!s)
		return (NULL);
	i = 0;
	j = -1;
	countstrings = ft_countstrings(s, c);
	splits = ft_calloc(sizeof(char *), (countstrings + 1));
	if (!splits)
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			splits[++j] = ft_strdup_split(s + i, c);
		while (s[i] && s[i] != c)
			i++;
	}
	return (splits);
}
