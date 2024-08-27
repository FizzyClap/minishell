/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:57:15 by roespici          #+#    #+#             */
/*   Updated: 2024/08/17 17:31:26 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_intlen(long int nb)
{
	int	i;

	i = 0;
	if (nb <= 0)
	{
		nb = -nb;
		i++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int nb)
{
	char		*tab;
	int			len;
	long int	n;

	n = nb;
	len = ft_intlen(n);
	tab = ft_calloc(sizeof(char), (len + 1));
	if (!tab)
		return (NULL);
	if (nb < 0)
		n = -n;
	while (len > 0)
	{
		tab[len - 1] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	if (nb < 0)
		tab[0] = '-';
	return (tab);
}
