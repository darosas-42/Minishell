/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darosas- <darosas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 04:54:24 by dreix             #+#    #+#             */
/*   Updated: 2025/11/12 20:40:03 by darosas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static void	exec_cd(char **paths, t_prompt *prompt)
{
	DIR		*dir;
	char	**cmds;
	int		result;

	g_status = 0;
	dir = NULL;
	cmds = ((t_mini *)prompt->cmds->content)->full_cmd;
	if (cmds && cmds[1])
		dir = opendir(cmds[1]);
	if (!cmds[1] && paths[0] && !paths[0][0])
		ft_putstr_fd("minishell: HOME not set\n", 2);
	if (!cmds[1] && paths[0])
		result = chdir(paths[0]);
	if (result == -1)
		g_status = 1;
	if (cmds[1] && dir && (access(cmds[1], F_OK) == 0))
		chdir(cmds[1]);
	else if (cmds[1] && (access(cmds[1], F_OK) == -1))
		ms_perror(NO_FL, cmds[1], 1);
	else if (cmds[1] && (access(cmds[1], X_OK) == -1))
		ms_perror(NO_PERM, cmds[1], 1);
	else if (cmds[1])
		ms_perror(ISNOT_DIR, cmds[1], 1);
	if (dir)
		closedir(dir);
}

int	ms_cd(t_prompt *prompt)
{
	char	**paths;
	char	**cmds;
	char	*str;

	cmds = ((t_mini *)prompt->cmds->content)->full_cmd;
	if (cmds && cmds[1] && cmds[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	str = ms_getenv("HOME", prompt->envp, 4);
	if (!str)
		str = ft_strdup("");
	paths = enlarge_matrix(NULL, str);
	free(str);
	str = getcwd(NULL, 0);
	if (!str)
		str = ft_strdup("");
	paths = enlarge_matrix(paths, str);
	free(str);
	exec_cd(paths, prompt);
	if (g_status == 0)
		prompt->envp = ms_setenv("OLDPWD", paths[1], prompt->envp, 6);
	str = getcwd(NULL, 0);
	if (!str)
		str = ft_strdup("");
	prompt->envp = ms_setenv("PWD", str, prompt->envp, 3);
	free(str);
	free_matrix(paths);
	return (g_status);
}
