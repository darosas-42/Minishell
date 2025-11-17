/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darosas- <darosas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 20:53:15 by dreix             #+#    #+#             */
/*   Updated: 2025/11/17 18:04:34 by darosas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	matrixlen(char **matrix)
{
	int	i;

	i = 0;
	while (matrix && matrix[i])
		i++;
	return (i);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = matrixlen(matrix);
	while (--i >= 0)
		free(matrix[i]);
	free(matrix);
}

char	**matrix_dup(char **matrix)
{
	char	**new;
	int		i;

	i = matrixlen(matrix);
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
	new[i] = NULL;
	return (new);
}

char	**enlarge_matrix(char **matrix, char *str)
{
	char	**new;
	int		i;

	i = matrixlen(matrix);
	new = malloc((i + 2) * sizeof(char *));
	if (!new || !str)
		return (matrix);
	i = 0;
	while (matrix && matrix[i])
	{
		new[i] = ft_strdup(matrix[i]);
		if (!new[i])
		{
			free_matrix(new);
			free_matrix(matrix);
		}
		i++;
	}
	new[i++] = ft_strdup(str);
	new[i] = NULL;
	if (matrix)
		free_matrix(matrix);
	return (new);
}

char	**bubble_sort(char **matrix)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (matrix && matrix[i] && matrix[i + 1])
	{
		j = 0;
		while (matrix[i][j] == matrix[i + 1][j])
			j++;
		if (matrix[i][j] > matrix[i + 1][j])
		{
			temp = matrix[i];
			matrix[i] = matrix[i + 1];
			matrix[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
	return (matrix);
}
