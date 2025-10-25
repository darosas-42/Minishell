/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darosas- <darosas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:19:16 by darosas-          #+#    #+#             */
/*   Updated: 2025/02/04 21:19:16 by darosas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen_gnl(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_calloc_gnl(size_t size, size_t type)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(size * type);
	if (!str)
		return (NULL);
	i = 0;
	while (i < (size * type))
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}

char	*ft_strjoin_gnl(const char *s1, const char *s2)
{
	char	*temp;
	int		i;
	int		j;
	int		len;

	len = ft_strlen_gnl(s1) + ft_strlen_gnl(s2);
	temp = ft_calloc_gnl((len + 1), sizeof(char));
	i = 0;
	while (s1[i])
	{
		temp[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		temp[i + j] = s2[j];
		j++;
	}
	return (temp);
}

int	ft_strchr_gnl(const char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}
