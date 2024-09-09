/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:45:52 by roespici          #+#    #+#             */
/*   Updated: 2024/09/06 10:37:58 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_count_args(char **args)
{
	int	count;

	count = 0;
	if (!args[0])
		return (count);
	count++;
	while (args[count])
		count++;
	return (count);
}
