/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darosas- <darosas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:13:18 by darosas-          #+#    #+#             */
/*   Updated: 2024/12/05 15:43:20 by darosas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	d_size;
	size_t	s_size;

	d_size = ft_strlen(dst);
	s_size = ft_strlen(src);
	if (d_size >= size)
		s_size += size;
	else
		s_size += d_size;
	if (size > 0)
	{
		i = 0;
		while (src[i] && d_size < (size - 1))
			dst[d_size++] = src[i++];
		dst[d_size] = '\0';
	}
	return (s_size);
}
