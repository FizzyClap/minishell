/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:21:28 by roespici          #+#    #+#             */
/*   Updated: 2024/09/02 08:08:40 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	dest = ft_calloc(sizeof(char), (len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = s[start + i];
		i++;
	}
	return (dest);
}
