/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreix <darosas-@student.42malaga.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 08:56:22 by dreix             #+#    #+#             */
/*   Updated: 2025/11/10 21:47:54 by dreix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_home(t_prompt prompt)
{
	char	*home;
	char	*pwd;
	char	*path;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("(no directory) ");
	home = ms_getenv("HOME", prompt.envp, 4);
	if (home && home[0] && ft_strnstr(pwd, home, ft_strlen(pwd)))
	{
		path = ft_strdup(&pwd[ft_strlen(home)]);
		free(pwd);
		pwd = ft_strjoin("~", path);
		free(path);
	}
	free(home);
	return (pwd);
}

static void	ms_whoami(char **str, char *cmd, char *path, char **envp)
{
	int		fd[2];
	pid_t	pid;
	char	**matrix;
	char	*temp;

	pipe(fd);
	pid = fork();
	if (!pid)
	{
		close(fd[FDREAD]);
		dup2(fd[FDWRITE], STDOUT_FILENO);
		matrix = enlarge_matrix(NULL, cmd);
		if (access(path, F_OK) == 0)
			execve(path, matrix, envp);
		free(matrix);
		exit (1);
	}
	close(fd[FDWRITE]);
	waitpid(pid, NULL, 0);
	temp = get_next_line(fd[FDREAD]);
	*str = ft_strtrim(temp, "\n");
	free(temp);
	close(fd[FDREAD]);
}

char	*get_prompt(t_prompt prompt)
{
	char	*str;
	char	*tmp;
	char	*tmp2;

	ms_whoami(&str, "whoami", "/usr/bin/whoami", prompt.envp);
	if (!str)
		str = ft_strdup("guest");
	tmp = ft_strjoin(str, "@minishell: ");
	free(str);
	str = get_home(prompt);
	tmp2 = ft_strjoin(tmp, str);
	free(tmp);
	free(str);
	str = ft_strjoin(tmp2, "$ ");
	free(tmp2);
	return (str);
}
