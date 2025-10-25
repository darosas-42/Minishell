/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darosas- <darosas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:33:25 by darosas-          #+#    #+#             */
/*   Updated: 2024/12/10 19:42:43 by darosas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free_all(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	while (--i >= 0)
		free(matrix[i]);
	free(matrix);
	return (NULL);
}

static char	**ft_splitting_words(char const *s, char c, int i, char **matrix)
{
	int	l;
	int	j;
	int	k;

	j = 0;
	while (s[++i])
	{
		l = -1;
		while (s[i + ++l] != c)
		{
			if (s[i + l] != c && (s[i + l + 1] == c || s[i + l + 1] == '\0'))
			{
				matrix[j] = (char *)malloc(sizeof(char) * (l + 2));
				if (!matrix[j])
					return (ft_free_all(matrix));
				k = 0;
				while (--l > -2)
					matrix[j][k++] = s[i++];
				i--;
				matrix[j++][k] = '\0';
				break ;
			}
		}
	}
	return (matrix);
}

char	**ft_split(char const *s, char c)
{
	char	**matrix;
	int		i;
	int		counter;

	i = -1;
	counter = 0;
	while (s[++i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			counter++;
	}
	matrix = (char **)malloc(sizeof(char *) * (counter + 1));
	if (!matrix)
		return (0);
	matrix[counter] = NULL;
	i = -1;
	matrix = ft_splitting_words(s, c, i, matrix);
	if (matrix == 0)
		return (0);
	return (matrix);
}
