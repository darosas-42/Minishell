/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmengiba <pmengiba@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:04:25 by pmengiba          #+#    #+#             */
/*   Updated: 2025/11/17 18:04:25 by pmengiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static int	process_here_line(char *str[2], char *limit)
{
	char	*temp;
	size_t	len;

	len = ft_strlen(str[0]);
	if (ft_strncmp(str[0], limit, len) == 0 && ft_strlen(limit) == len)
	{
		free(str[0]);
		return (1);
	}
	temp = str[0];
	str[0] = ft_strjoin(str[0], "\n");
	free(temp);
	temp = str[1];
	str[1] = ft_strjoin(str[1], str[0]);
	free(temp);
	free(str[0]);
	return (0);
}

static char	*get_here_str(char *str[2], size_t len, char *limit, char *warn)
{
	(void)len;
	if (!str[1])
		str[1] = ft_strdup("");
	while (g_status != 130)
	{
		if (str[0] && process_here_line(str, limit))
			break ;
		str[0] = readline("> ");
		if (!str[0])
		{
			printf("%s (wanted `%s\')\n", warn, limit);
			break ;
		}
	}
	return (str[1]);
}

int	get_here_doc(char *str[2], char *aux[2])
{
	int		fd[2];

	g_status = 0;
	if (pipe(fd) == -1)
	{
		ms_perror(PIPERROR, NULL, 1);
		return (-1);
	}
	str[1] = get_here_str(str, 0, aux[0], aux[1]);
	write(fd[FDWRITE], str[1], ft_strlen(str[1]));
	free(str[1]);
	close(fd[FDWRITE]);
	if (g_status == 130)
	{
		close(fd[FDREAD]);
		return (-1);
	}
	return (fd[FDREAD]);
}
