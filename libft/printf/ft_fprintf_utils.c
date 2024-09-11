/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:42:13 by roespici          #+#    #+#             */
/*   Updated: 2024/09/11 14:32:31 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	ft_fputchar(int fd, char c)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_fputhexa(int fd, unsigned long nb, char *format)
{
	int	count;

	count = 0;
	if (nb >= 16)
	{
		count += ft_fputhexa(fd, nb / 16, format);
		count += ft_fputhexa(fd, nb % 16, format);
	}
	else
	{
		if (*format == 'X')
			count += ft_fputchar(fd, "0123456789ABCDEF"[nb % 16]);
		else
			count += ft_fputchar(fd, "0123456789abcdef"[nb % 16]);
	}
	return (count);
}

int	ft_fputnbr(int fd, long long int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n = -n;
		count += ft_fputchar(fd, '-');
	}
	if (n > 9)
	{
		count += ft_fputnbr(fd, n / 10);
		count += ft_fputnbr(fd, n % 10);
	}
	if (n >= 0 && n <= 9)
		count += ft_fputchar(fd, n + '0');
	return (count);
}

int	ft_fputstr(int fd, char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (ft_fputstr(fd, "(null)"));
	while (str[i])
	{
		count += ft_fputchar(fd, str[i]);
		i++;
	}
	return (count);
}
