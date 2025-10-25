/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darosas- <darosas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 20:29:24 by darosas-          #+#    #+#             */
/*   Updated: 2024/12/23 17:52:01 by darosas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_filter(char const *str, int i, va_list args)
{
	int	counter;

	counter = 0;
	if (str[i] == 'c')
		counter += ft_putchar(va_arg(args, int));
	else if (str[i] == 's')
		counter += ft_putstr(va_arg(args, char *));
	else if (str[i] == 'p')
		counter += ft_address(va_arg(args, unsigned long));
	else if (str[i] == 'd' || str[i] == 'i')
		counter += ft_putnbr(va_arg(args, int));
	else if (str[i] == 'u')
		counter += ft_unsnb(va_arg(args, unsigned int));
	else if (str[i] == 'x' || str[i] == 'X')
		counter += ft_hexadec(va_arg(args, unsigned int), str[i]);
	else if (str[i] == '%')
		counter += ft_putchar('%');
	return (counter);
}

int	ft_printf(char const *str, ...)
{
	va_list	args;
	int		i;
	int		counter;

	va_start(args, str);
	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			counter += ft_filter(str, i, args);
		}
		else
			counter += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (counter);
}

/* int	main(void)
{
	ft_printf(" %p ", ptr);
} */
