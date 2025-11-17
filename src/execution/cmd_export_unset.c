/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darosas- <darosas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 07:30:04 by dreix             #+#    #+#             */
/*   Updated: 2025/11/17 19:18:54 by darosas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_var(char *var, char **envp, int *j, int unset)
{
	int	equal;

	equal = strchr_index(var, '=');
	if (unset == 1)
		equal = ft_strlen(var);
	if (equal == 0)
		return (2);
	if (equal < 0)
		return (3);
	*j = 0;
	while (envp[*j])
	{
		if (!ft_strncmp(var, envp[*j], equal) && envp[*j][equal] == '=')
			return (1);
		(*j)++;
	}
	return (0);
}

static int	export_var(t_prompt *prompt, char *var)
{
	int	j;
	int	result;

	if (!is_valid_var_name(var))
	{
		export_error(prompt, var, 1);
		return (1);
	}
	result = find_var(var, prompt->envp, &j, 0);
	if (result == 1)
	{
		free((prompt->envp)[j]);
		(prompt->envp)[j] = ft_strdup(var);
	}
	else if (result == 0)
		prompt->envp = enlarge_matrix(prompt->envp, var);
	return (0);
}

int	ms_export(t_prompt *prompt)
{
	char	**cmd;
	char	**matrix;
	int		i;
	int		exit_code;

	cmd = ((t_mini *)prompt->cmds->content)->full_cmd;
	if (matrixlen(cmd) == 1)
	{
		matrix = matrix_dup(prompt->envp);
		matrix = bubble_sort(matrix);
		i = -1;
		while (matrix[++i])
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putendl_fd(matrix[i], 1);
		}
		free(matrix);
		return (0);
	}
	i = 0;
	exit_code = 0;
	while (cmd[++i])
		exit_code |= export_var(prompt, cmd[i]);
	return (exit_code);
}

static char	**matrix_dup_but_n(char **matrix, int n)
{
	char	**new;
	int		i[2];

	i[0] = matrixlen(matrix);
	new = malloc((i[0]) * sizeof(char *));
	if (!new)
		return (NULL);
	i[0] = -1;
	i[1] = -1;
	while (matrix && matrix[++i[0]])
	{
		if (i[0] != n)
		{
			new[++i[1]] = ft_strdup(matrix[i[0]]);
			if (!new[i[1]])
			{
				free_matrix(new);
				free_matrix(matrix);
				return (NULL);
			}
		}
	}
	new[i[1] + 1] = NULL;
	free_matrix(matrix);
	return (new);
}

int	ms_unset(t_prompt *prompt)
{
	char	**cmd;
	int		i;
	int		j;

	cmd = ((t_mini *)prompt->cmds->content)->full_cmd;
	i = 0;
	while (cmd[i])
		i++;
	if (i < 2)
		return (0);
	i = 0;
	while (cmd[++i])
	{
		if (find_var(cmd[i], prompt->envp, &j, 1) == 1)
			prompt->envp = matrix_dup_but_n(prompt->envp, j);
	}
	return (0);
}
