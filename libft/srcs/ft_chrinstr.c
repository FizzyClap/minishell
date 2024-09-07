/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrinstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:54:54 by roespici          #+#    #+#             */
/*   Updated: 2024/09/06 09:37:16 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_chrinstr(char *str, int c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == (char)c)
			return (0);
	return (1);
}
