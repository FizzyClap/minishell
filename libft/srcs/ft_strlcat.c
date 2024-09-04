/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:35:43 by roespici          #+#    #+#             */
/*   Updated: 2024/09/02 08:07:42 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	dst_size;
	size_t	src_size;
	size_t	i;

	dst_size = ft_strlen((char *)dst);
	src_size = ft_strlen((char *)src);
	i = 0;
	if (size <= dst_size)
		return (src_size + size);
	while (src[i] && i < size - dst_size - 1)
	{
		dst[dst_size + i] = src[i];
		i++;
	}
	dst[dst_size + i] = '\0';
	return (dst_size + src_size);
}
