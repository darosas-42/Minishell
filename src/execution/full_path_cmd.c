/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_path_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darosas- <darosas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:41:48 by dreix             #+#    #+#             */
/*   Updated: 2025/11/17 19:35:18 by darosas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_return_gnb(t_mini *node, int i[2])
{
	free(node->full_path);
	if (i[1] == 1)
		return ("NO_PERM");
	return (NULL);
}

static char	*get_not_builtin(char **matrix, t_mini *node, char *tmp)
{
	int		i[2];

	node->full_path = NULL;
	i[0] = -1;
	i[1] = 0;
	while (matrix && matrix[++i[0]])
	{
		tmp = ft_strjoin(matrix[i[0]], "/");
		if (!tmp)
			return (NULL);
		free(node->full_path);
		node->full_path = ft_strjoin(tmp, node->full_cmd[0]);
		free(tmp);
		if (!node->full_path)
			return (NULL);
		if (access(node->full_path, F_OK) == 0)
		{
			i[1] = 1;
			if (access(node->full_path, X_OK) == 0)
				break ;
		}
	}
	if (!matrix || !matrix[i[0]])
		return (handle_return_gnb(node, i));
	return (node->full_path);
}

static void	*checks_cmd(t_prompt *prompt, t_list *cmd, DIR *dir, char **matrix)
{
	t_mini	*node;
	char	*path;

	node = cmd->content;
	if (node && node->full_cmd && ft_strchr(*node->full_cmd, '/') && !dir)
	{
		matrix = ft_split(node->full_cmd[0], '/');
		node->full_path = ft_strdup(node->full_cmd[0]);
		free(node->full_cmd[0]);
		node->full_cmd[0] = ft_strdup(matrix[matrixlen(matrix) - 1]);
	}
	else if (node && node->full_cmd && !dir)
	{
		path = ms_getenv("PATH", prompt->envp, 4);
		if (!path)
			return (ms_perror(prompt, NO_FL, node->full_cmd[0], 1));
		matrix = ft_split(path, ':');
		free(path);
		node->full_path = get_not_builtin(matrix, node, NULL);
		if (!node->full_path || !node->full_cmd[0] || !node->full_cmd[0][0])
			ms_perror(prompt, NO_CMD, node->full_cmd[0], 127);
	}
	free_matrix(matrix);
	return (NULL);
}

void	get_full_path(t_prompt *prompt, t_list *cmd, DIR *dir)
{
	t_mini	*node;

	node = cmd->content;
	if (is_builtin(node))
		return ;
	checks_cmd(prompt, cmd, dir, NULL);
	if (node && node->full_cmd && dir && ft_strchr(node->full_cmd[0], '/'))
		ms_perror(prompt, IS_DIR, node->full_cmd[0], 126);
	else if (node && node->full_cmd && dir)
		ms_perror(prompt, NO_CMD, node->full_cmd[0], 127);
	else if (node && node->full_path
		&& !ft_strncmp(node->full_path, "NO_PERM", 7))
		ms_perror(prompt, NO_PERM, node->full_cmd[0], 126);
	else if (node && node->full_path && access(node->full_path, F_OK) == -1)
		ms_perror(prompt, NO_FL, node->full_path, 127);
	else if (node && node->full_path && access(node->full_path, X_OK) == -1)
		ms_perror(prompt, NO_PERM, node->full_path, 126);
}
