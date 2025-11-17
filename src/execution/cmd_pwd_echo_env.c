/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd_echo_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darosas- <darosas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:53:02 by dreix             #+#    #+#             */
/*   Updated: 2025/11/17 18:04:05 by darosas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	ft_putendl_fd(path, 1);
	free(path);
	return (0);
}

int	ms_env(t_prompt *prompt)
{
	char	**envp;
	int		i;

	envp = prompt->envp;
	i = -1;
	while (envp && envp[++i])
		ft_putendl_fd(envp[i], 1);
	return (0);
}

static int	echo_check_n(char *str, int *newline)
{
	int	i;

	i = 1;
	if (str[0] != '-' || str[1] != 'n')
		return (0);
	while (str[++i])
	{
		if (str[i] != 'n')
			return (0);
	}
	*newline = 0;
	return (1);
}

int	ms_echo(t_list *cmd)
{
	t_mini	*node;
	int		i;
	int		newline;

	i = 0;
	newline = 1;
	node = cmd->content;
	while (node->full_cmd && node->full_cmd[++i])
	{
		if (!echo_check_n(node->full_cmd[i], &newline))
			break ;
	}
	while (node->full_cmd && node->full_cmd[i])
	{
		ft_putstr_fd(node->full_cmd[i], 1);
		if (node->full_cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline == 1)
		write(1, "\n", 1);
	return (0);
}
