/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexadec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darosas- <darosas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:16:17 by darosas-          #+#    #+#             */
/*   Updated: 2024/12/18 22:57:56 by darosas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexadec(unsigned long nb, char c)
{
	int	i;

	i = 0;
	if (nb >= 16)
		i += ft_hexadec(nb / 16, c);
	if (c == 'x')
		ft_putchar("0123456789abcdef"[nb % 16]);
	else
		ft_putchar("0123456789ABCDEF"[nb % 16]);
	i++;
	return (i);
}
