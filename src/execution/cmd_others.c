/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_others.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darosas- <darosas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:30:47 by dreix             #+#    #+#             */
/*   Updated: 2025/11/17 19:32:04 by darosas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_others_cleanup(DIR *dir, int *fd, int cleanfd)
{
	if (cleanfd)
	{
		close(fd[FDREAD]);
		close(fd[FDWRITE]);
	}
	if (dir)
		closedir(dir);
}

static void	cmd_others_handle_pipe(t_list *cmd, int fd[2])
{
	t_mini	*next;

	close(fd[FDWRITE]);
	if (cmd->next)
	{
		next = cmd->next->content;
		if (!next->infile)
			next->infile = fd[FDREAD];
		else
			close(fd[FDREAD]);
	}
	else
		close(fd[FDREAD]);
}

static void	cmd_others_close_redirs(t_list *cmd)
{
	t_mini	*node;

	node = cmd->content;
	if (node->infile > 2)
		close(node->infile);
	if (node->outfile > 2)
		close(node->outfile);
}

void	*cmd_others(t_prompt *prompt, t_list *cmd)
{
	int		fd[2];
	DIR		*dir;

	dir = NULL;
	if ((t_mini *)cmd->content && ((t_mini *)cmd->content)->full_cmd)
		dir = opendir(*((t_mini *)cmd->content)->full_cmd);
	get_full_path(prompt, cmd, dir);
	if (pipe(fd) == -1)
	{
		cmd_others_cleanup(dir, fd, 0);
		return (ms_perror(prompt, PIPERROR, NULL, 1));
	}
	if (!fork_cmd(prompt, cmd, fd))
	{
		cmd_others_cleanup(dir, fd, 1);
		return (NULL);
	}
	cmd_others_handle_pipe(cmd, fd);
	cmd_others_close_redirs(cmd);
	cmd_others_cleanup(dir, fd, 0);
	return (NULL);
}
