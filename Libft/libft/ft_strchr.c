/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darosas- <darosas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:59:10 by darosas-          #+#    #+#             */
/*   Updated: 2024/12/05 17:56:42 by darosas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	c2;

	i = 0;
	c2 = (char)c;
	while (s[i])
	{
		if (s[i] == c2)
			return ((char *)&s[i]);
		i++;
	}
	if (c2 == '\0')
		return ((char *)&s[i]);
	return (0);
}
