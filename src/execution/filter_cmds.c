/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darosas- <darosas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:19:49 by dreix             #+#    #+#             */
/*   Updated: 2025/11/17 19:24:55 by darosas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_mini *node)
{
	int	i;

	if (!node->full_cmd)
		return (0);
	i = ft_strlen(node->full_cmd[0]);
	if (!ft_strncmp(node->full_cmd[0], "echo", i) && i == 4)
		return (1);
	if (!ft_strncmp(node->full_cmd[0], "cd", i) && i == 2)
		return (1);
	if (!ft_strncmp(node->full_cmd[0], "pwd", i) && i == 3)
		return (1);
	if (!ft_strncmp(node->full_cmd[0], "export", i) && i == 6)
		return (1);
	if (!ft_strncmp(node->full_cmd[0], "unset", i) && i == 5)
		return (1);
	if (!ft_strncmp(node->full_cmd[0], "env", i) && i == 3)
		return (1);
	if (!ft_strncmp(node->full_cmd[0], "exit", i) && i == 4)
		return (1);
	return (0);
}

int	builtin(t_prompt *prompt, t_list *cmd, int *is_exit)
{
	char	**ptr;
	int		i;

	while (cmd)
	{
		ptr = ((t_mini *)cmd->content)->full_cmd;
		i = 0;
		if (ptr && ptr[0])
			i = ft_strlen(*ptr);
		if (!cmd->next && ptr && !ft_strncmp("cd", *ptr, i) && i == 2)
			prompt->e_status = ms_cd(prompt);
		else if (!cmd->next && ptr && !ft_strncmp("export", *ptr, i) && i == 6)
			prompt->e_status = ms_export(prompt);
		else if (!cmd->next && ptr && !ft_strncmp("unset", *ptr, i) && i == 5)
			prompt->e_status = ms_unset(prompt);
		else if (ptr && !ft_strncmp("exit", *ptr, i) && i == 4)
			prompt->e_status = ms_exit(cmd, is_exit);
		else
		{
			signals_not_interactive();
			cmd_others(prompt, cmd);
		}
		cmd = cmd->next;
	}
	return (prompt->e_status);
}
