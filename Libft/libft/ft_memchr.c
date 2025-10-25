/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darosas- <darosas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:32:17 by darosas-          #+#    #+#             */
/*   Updated: 2024/12/13 18:03:03 by darosas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*s2;
	char	c2;
	size_t	i;

	s2 = (char *)s;
	c2 = (char)c;
	i = 0;
	while (i < n)
	{
		if (s2[i] == c2)
			return ((void *)&s2[i]);
		i++;
	}
	return (0);
}
