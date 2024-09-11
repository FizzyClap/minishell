/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:07:08 by roespici          #+#    #+#             */
/*   Updated: 2024/09/11 13:41:58 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_puthexa(unsigned long nb, char *format)
{
	int	count;

	count = 0;
	if (nb >= 16)
	{
		count += ft_puthexa(nb / 16, format);
		count += ft_puthexa(nb % 16, format);
	}
	else
	{
		if (*format == 'X')
			count += ft_putchar("0123456789ABCDEF"[nb % 16]);
		else
			count += ft_putchar("0123456789abcdef"[nb % 16]);
	}
	return (count);
}

int	ft_putnbr(long long int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n = -n;
		count += ft_putchar('-');
	}
	if (n > 9)
	{
		count += ft_putnbr(n / 10);
		count += ft_putnbr(n % 10);
	}
	if (n >= 0 && n <= 9)
		count += ft_putchar(n + '0');
	return (count);
}

int	ft_putstr(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (ft_putstr("(null)"));
	while (str[i])
	{
		count += ft_putchar(str[i]);
		i++;
	}
	return (count);
}
