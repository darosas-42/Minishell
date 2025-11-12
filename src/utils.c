/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreix <darosas-@student.42malaga.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 20:53:15 by dreix             #+#    #+#             */
/*   Updated: 2025/10/30 17:40:27 by dreix            ###   ########.fr       */
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
