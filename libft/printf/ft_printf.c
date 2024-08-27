/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 07:53:44 by roespici          #+#    #+#             */
/*   Updated: 2024/05/11 15:40:59 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static int	ft_typep(unsigned long nb, char *format)
{
	int	count;

	count = 0;
	if (nb == 0)
		return (ft_putstr("(nil)"));
	count += ft_putstr("0x");
	count += ft_puthexa(nb, (char *)format);
	return (count);
}

int	ft_type(va_list args, char *format)
{
	int	count;

	count = 0;
	if (*format == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (*format == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (*format == 'p')
		count += ft_typep(va_arg(args, unsigned long), (char *)format);
	else if (*format == 'd' || *format == 'i')
		count += ft_putnbr(va_arg(args, int));
	else if (*format == 'u')
		count += ft_putnbr(va_arg(args, unsigned int));
	else if (*format == 'x' || *format == 'X')
		count += ft_puthexa(va_arg(args, unsigned int), (char *)format);
	else if (*format == '%')
		count += ft_putchar('%');
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		count;

	va_start(args, str);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			count += ft_type(args, (char *)str + i);
		}
		else
			count += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (count);
}
