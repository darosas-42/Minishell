/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmengiba <pmengiba@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:04:20 by pmengiba          #+#    #+#             */
/*   Updated: 2025/11/17 18:04:20 by pmengiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	get_fd(int oldfd, char *path, int flags[2])
{
	int	fd;

	if (oldfd > 2)
		close(oldfd);
	if (!path)
		return (-1);
	if (access(path, F_OK) == -1 && !flags[0])
		ms_perror(NO_FL, path, 127);
	else if (!flags[0] && access(path, R_OK) == -1)
		ms_perror(NO_PERM, path, 126);
	else if (flags[0] && access(path, W_OK) == -1 && access(path, F_OK) == 0)
		ms_perror(NO_PERM, path, 126);
	if (flags[0] && flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (flags[0] && !flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (!flags[0] && oldfd != -1)
		fd = open(path, O_RDONLY);
	else
		fd = oldfd;
	return (fd);
}

t_mini	*get_outfile1(t_mini *node, char **args, int *i)
{
	char	*nl;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 0;
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[*i] && node->outfile != -1 && node->infile != -1)
		node->outfile = get_fd(node->outfile, args[*i], flags);
	if (!args[*i])
	{
		*i = -1;
		ft_putendl_fd(nl, 2);
		g_status = 2;
	}
	return (node);
}

t_mini	*get_outfile2(t_mini *node, char **args, int *i)
{
	char	*nl;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 1;
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[++(*i)] && node->outfile != -1 && node->infile != -1)
		node->outfile = get_fd(node->outfile, args[*i], flags);
	if (!args[*i])
	{
		*i = -1;
		ft_putendl_fd(nl, 2);
		g_status = 2;
	}
	return (node);
}

t_mini	*get_infile1(t_mini *node, char **args, int *i)
{
	char	*nl;
	int		flags[2];

	flags[0] = 0;
	flags[1] = 0;
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[*i] && node->infile != -1)
		node->infile = get_fd(node->infile, args[*i], flags);
	if (!args[*i])
	{
		*i = -1;
		ft_putendl_fd(nl, 2);
		g_status = 2;
	}
	return (node);
}

t_mini	*get_infile2(t_mini *node, char **args, int *i)
{
	char	*aux[2];
	char	*nl;
	char	*str[2];

	str[0] = NULL;
	str[1] = NULL;
	aux[0] = NULL;
	aux[1] = "minishell: warning: here-document delimited by end-of-file";
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[++(*i)])
	{
		aux[0] = args[*i];
		node->infile = get_here_doc(str, aux);
	}
	if (!args[*i] || node->infile == -1)
	{
		*i = -1;
		if (node->infile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_status = 2;
		}
	}
	return (node);
}
