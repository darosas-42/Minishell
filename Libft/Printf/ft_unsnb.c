/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsnb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darosas- <darosas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:15:59 by darosas-          #+#    #+#             */
/*   Updated: 2024/12/17 22:37:21 by darosas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_unsnb(unsigned int nb)
{
	char	c;
	int		i;

	if (nb > 9)
		ft_putnbr(nb / 10);
	c = (nb % 10) + '0';
	write(1, &c, 1);
	i = 0;
	while (nb > 9)
	{
		nb /= 10;
		i++;
	}
	return (i + 1);
}
