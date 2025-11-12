/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreix <darosas-@student.42malaga.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:03:09 by dreix             #+#    #+#             */
/*   Updated: 2025/11/11 00:15:22 by dreix            ###   ########.fr       */
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

void	free_cmd(void *content)
{
	t_mini	*node;

	node = content;
	free_matrix(node->full_cmd);
	free(node->full_path);
	if (node->infile != STDIN_FILENO)
		close(node->infile);
	if (node->outfile != STDOUT_FILENO)
		close(node->outfile);
	free(node);
}

int	ft_strchars_i(const char *s, const char *set)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (set[j])
		{
			if (s[i] == set[j])
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

void	ft_matrix_replace_in(char ***m, char **replacement, int pos)
{
	char	**new;
	int		i[2];

	if (!m || !*m)
		return ;
	i[0] = matrixlen(*m);
	i[1] = 0;
	if (replacement)
		i[1] = matrixlen(replacement);
	new = malloc(sizeof(char *) * (i[0] - 1 + i[1] + 1));
	if (!new)
		return ;
	i[0] = -1;
	i[1] = 0;
	while (++i[0] < pos && (*m)[i[0]])
		new[i[1]++] = (*m)[i[0]];
	if ((*m)[i[0]])
		free((*m)[i[0]++]);
	while (replacement && *replacement)
		new[i[1]++] = ft_strdup(*replacement++);
	while ((*m)[i[0]])
		new[i[1]++] = (*m)[i[0]++];
	new[i[1]] = NULL;
	free(*m);
	*m = new;
}
