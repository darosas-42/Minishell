/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darosas- <darosas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:48:51 by darosas-          #+#    #+#             */
/*   Updated: 2024/12/04 21:13:32 by darosas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	i;

	ptr = (char *)malloc(nmemb * size);
	if (!ptr)
		return (0);
	i = 0;
	while (i < (nmemb * size))
		ptr[i++] = '\0';
	return (ptr);
}
