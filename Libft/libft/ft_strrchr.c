/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darosas- <darosas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:29:00 by darosas-          #+#    #+#             */
/*   Updated: 2024/12/03 18:20:32 by darosas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	c2;

	c2 = (char)c;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == c2)
			return ((char *)&s[i]);
		i--;
	}
	return (0);
}
