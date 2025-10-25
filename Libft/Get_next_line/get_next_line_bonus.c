/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darosas- <darosas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:18:36 by darosas-          #+#    #+#             */
/*   Updated: 2025/02/04 21:18:36 by darosas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*cleaner(char *static_str)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (static_str[i] != '\n' && static_str[i] != '\0')
		i++;
	if (static_str[i] == '\0')
	{
		free(static_str);
		return (NULL);
	}
	temp = ft_calloc_gnl((ft_strlen_gnl(static_str) + 1 - i), sizeof(char));
	j = 0;
	i++;
	while (static_str[i] != '\0')
		temp[j++] = static_str[i++];
	free(static_str);
	return (temp);
}

static char	*get_good_line(char *static_str)
{
	char	*temp;
	int		i;

	i = 0;
	if (static_str[i] == '\0')
		return (NULL);
	while (static_str[i] != '\n' && static_str[i] != '\0')
		i++;
	i++;
	temp = ft_calloc_gnl((i + ft_strchr_gnl(static_str, '\n')), sizeof(char));
	i = 0;
	while (static_str[i] != '\n' && static_str[i] != '\0')
	{
		temp[i] = static_str[i];
		i++;
	}
	if (ft_strchr_gnl(static_str, '\n'))
		temp[i] = '\n';
	return (temp);
}

static char	*ft_strjoin2_gnl(char *s1, char *s2)
{
	char	*temp;

	temp = ft_strjoin_gnl(s1, s2);
	free(s1);
	return (temp);
}

static char	*read_all(int fd, char *static_str)
{
	int		reader;
	char	*temp;

	if (!static_str)
		static_str = ft_calloc_gnl(1, sizeof(char));
	temp = ft_calloc_gnl((BUFFER_SIZE + 1), sizeof(char));
	reader = 1;
	while (reader > 0)
	{
		reader = read(fd, temp, BUFFER_SIZE);
		if (reader < 0)
		{
			free(static_str);
			static_str = NULL;
			free(temp);
			return (NULL);
		}
		temp[reader] = '\0';
		static_str = ft_strjoin2_gnl(static_str, temp);
		if (ft_strchr_gnl(temp, '\n'))
			break ;
	}
	free(temp);
	return (static_str);
}

char	*get_next_line(int fd)
{
	static char	*static_str[1024];
	char		*good_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	static_str[fd] = read_all(fd, static_str[fd]);
	if (static_str[fd] == NULL)
		return (NULL);
	good_line = get_good_line(static_str[fd]);
	if (good_line == NULL)
		return (free(static_str[fd]), static_str[fd] = NULL, NULL);
	static_str[fd] = cleaner(static_str[fd]);
	if (static_str[fd] == NULL)
		return (free(static_str[fd]), static_str[fd] = NULL, good_line);
	return (good_line);
}

/* int	main(void)
{
	int		fichero1;
	int		fichero2;
	int		fichero3;
	char	*line;

	fichero1 = open("archivo.txt", 0);
	fichero2 = open("archivo2.txt", O_RDONLY);
	fichero3 = open("archivo3.txt", O_RDONLY);
	line = get_next_line(fichero1);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fichero1);
	}
	free(line);
	printf("\n\n");
	line = get_next_line(fichero2);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fichero2);
	}
	free(line);
	printf("\n\n");
	line = get_next_line(fichero3);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fichero3);
	}
	printf("\n\n");
	close(fichero1);
	close(fichero2);
	close(fichero3);
	free(line);
} */
