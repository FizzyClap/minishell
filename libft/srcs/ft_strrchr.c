/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:15:53 by roespici          #+#    #+#             */
/*   Updated: 2024/09/02 08:07:42 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(char *s, int c)
{
	size_t	i;

	if (ft_strlen(s) == 0)
	{
		if (c == '\0')
			return ((char *)s);
		return (NULL);
	}
	i = ft_strlen((char *)s) - 1;
	c = (unsigned char)c;
	if (c == '\0')
		return ((char *)s + ft_strlen(s));
	while (s[i] && s[i] != c)
		i--;
	if (s[i] == c)
		return ((char *)s + i);
	return (NULL);
}
