/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:45:07 by roespici          #+#    #+#             */
/*   Updated: 2024/09/11 14:03:39 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static int	ft_ftypep(int fd, unsigned long nb, char *format)
{
	int	count;

	count = 0;
	if (nb == 0)
		return (ft_fputstr(fd, "(nil)"));
	count += ft_fputstr(fd, "0x");
	count += ft_fputhexa(fd, nb, (char *)format);
	return (count);
}

int	ft_ftype(int fd, va_list args, char *format)
{
	int	count;

	count = 0;
	if (*format == 'c')
		count += ft_fputchar(fd, va_arg(args, int));
	else if (*format == 's')
		count += ft_fputstr(fd, va_arg(args, char *));
	else if (*format == 'p')
		count += ft_ftypep(fd, va_arg(args, unsigned long), (char *)format);
	else if (*format == 'd' || *format == 'i')
		count += ft_fputnbr(fd, va_arg(args, int));
	else if (*format == 'u')
		count += ft_fputnbr(fd, va_arg(args, unsigned int));
	else if (*format == 'x' || *format == 'X')
		count += ft_fputhexa(fd, va_arg(args, unsigned int), (char *)format);
	else if (*format == '%')
		count += ft_fputchar(fd, '%');
	return (count);
}

int	ft_fprintf(int fd, char *str, ...)
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
			count += ft_ftype(fd, args, (char *)str + i);
		}
		else
			count += ft_fputchar(fd, str[i]);
		i++;
	}
	va_end(args);
	return (count);
}
