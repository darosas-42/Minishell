/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darosas- <darosas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:19:36 by dreix             #+#    #+#             */
/*   Updated: 2025/11/17 20:10:13 by darosas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*fork_redirec(t_prompt *prompt, t_list *cmd, int fd[2])
{
	t_mini	*node;

	node = cmd->content;
	if (node->infile != STDIN_FILENO)
	{
		if (dup2(node->infile, STDIN_FILENO) == -1)
			return (ms_perror(prompt, DUPERROR, NULL, 1));
		close(node->infile);
	}
	if (node->outfile != STDOUT_FILENO)
	{
		if (dup2(node->outfile, STDOUT_FILENO) == -1)
			return (ms_perror(prompt, DUPERROR, NULL, 1));
		close(node->outfile);
	}
	else if (cmd->next && dup2(fd[FDWRITE], STDOUT_FILENO) == -1)
		return (ms_perror(prompt, DUPERROR, NULL, 1));
	close(fd[FDWRITE]);
	return (NULL);
}

static void	fork_exec_cmd(t_prompt *prompt, t_list *cmd)
{
	t_mini	*node;
	int		size;

	node = cmd->content;
	size = ft_strlen(node->full_cmd[0]);
	signals_default();
	if (node->full_cmd && !is_builtin(node))
		execve(node->full_path, node->full_cmd, prompt->envp);
	else if (node->full_cmd && !ft_strncmp(node->full_cmd[0], "pwd", size)
		&& size == 3)
		prompt->e_status = ms_pwd();
	else if (node->full_cmd && !ft_strncmp(node->full_cmd[0], "echo", size)
		&& size == 4)
		prompt->e_status = ms_echo(cmd);
	else if (node->full_cmd && !ft_strncmp(node->full_cmd[0], "env", size)
		&& size == 3)
		prompt->e_status = ms_env(prompt);
}

static void	free_child_process(t_prompt *prompt)
{
	ft_lstclear(&prompt->cmds, free_cmd);
	free_matrix(prompt->envp);
}

static void	fork_child_process(t_prompt *prompt, t_list *cmd, int fd[2])
{
	t_mini	*n;

	n = cmd->content;
	if (n->infile == -1 || n->outfile == -1)
	{
		free_child_process(prompt);
		exit(1);
	}
	if ((n->full_path && access(n->full_path, X_OK) == 0) || is_builtin(n))
	{
		fork_redirec(prompt, cmd, fd);
		close(fd[FDREAD]);
		fork_exec_cmd(prompt, cmd);
		free_child_process(prompt);
		exit(prompt->e_status);
	}
	free_child_process(prompt);
	exit(prompt->e_status);
}

int	fork_cmd(t_prompt *prompt, t_list *cmd, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(fd[FDREAD]);
		close(fd[FDWRITE]);
		ms_perror(prompt, FORKERROR, NULL, 1);
		return (0);
	}
	else if (!pid)
		fork_child_process(prompt, cmd, fd);
	return (1);
}
