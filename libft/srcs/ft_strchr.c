/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:11:37 by roespici          #+#    #+#             */
/*   Updated: 2024/09/02 15:11:06 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_strchr(char *s, int c)
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
