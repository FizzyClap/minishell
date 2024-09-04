/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:06:53 by roespici          #+#    #+#             */
/*   Updated: 2024/09/02 08:07:42 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(char *s)
{
	int		i;
	char	*dest;

	i = 0;
	dest = ft_calloc(sizeof(char), (ft_strlen((char *)s) + 1));
	if (!dest)
		return (NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	return (dest);
}
