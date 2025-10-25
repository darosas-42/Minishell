/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreix <darosas-@student.42malaga.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 20:53:15 by dreix             #+#    #+#             */
/*   Updated: 2025/10/24 06:05:24 by dreix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strchr_index(const char *s, int c)
{
	int		i;
	char	c2;

	i = 0;
	c2 = (char)c;
	while (s[i])
	{
		if (s[i] == c2)
			return (i);
		i++;
	}
	if (c2 == '\0')
		return (i);
	return (-1);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix && matrix[i])
		i++;
	while (--i >= 0)
		free(matrix[i]);
	free(matrix);
}

char **matrix_dup(char **matrix)
{
	char	**new;
	int		i;

	i = 0;
	while (matrix && matrix[i])
		i++;
	new = malloc((i + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (matrix && matrix[i])
	{
		new[i] = ft_strdup(matrix[i]);
		if (!new[i])
		{
			free_matrix(new);
			return (NULL);
		}
		i++;
	}
	new[i] == NULL;
	return (new);
}

char	**enlarge_matrix(char **matrix, char *str)
{
	char	**new;
	int		i;

	i = 0;
	while (matrix && matrix[i])
		i++;
	new = malloc((i + 2) * sizeof(char *));
	if (!new || !str)
		return (matrix);
	i = 0;
	while (matrix && matrix[i])
	{
		new = ft_strdup(matrix[i]);
		if (!new[i])
		{
			free_matrix(new);
			free_matrix(matrix);
		}
	}
	new[i++] = ft_strdup(str);
	new[i] = NULL;
	free_matrix(matrix);
	return (new);
}
