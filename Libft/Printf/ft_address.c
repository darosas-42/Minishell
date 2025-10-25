/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_address.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darosas- <darosas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:11:55 by darosas-          #+#    #+#             */
/*   Updated: 2024/12/18 22:49:33 by darosas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_address(unsigned long nb)
{
	int	x;

	if (nb == 0)
		return (ft_putstr("(nil)"));
	x = ft_putstr("0x");
	x += ft_hexadec(nb, 'x');
	return (x);
}
