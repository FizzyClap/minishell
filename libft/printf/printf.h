/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:00:03 by roespici          #+#    #+#             */
/*   Updated: 2024/05/11 15:29:33 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_printf(const char *format, ...);
int	ft_puthexa(unsigned long nb, char *fornat);
int	ft_putstr(char *s);
int	ft_putnbr(long long int n);
int	ft_putchar(char c);

#endif
