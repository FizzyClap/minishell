/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 09:27:51 by roespici          #+#    #+#             */
/*   Updated: 2024/09/07 09:51:13 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_strisnum(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if ((str[i] == '+' || str[i] == '-') && i == 0)
			continue ;
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}
