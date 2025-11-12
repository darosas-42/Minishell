/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbueno-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:17:00 by mbueno-g          #+#    #+#             */
/*   Updated: 2022/03/14 17:19:55 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

/**
 * process_here_line - Procesa y acumula una línea del heredoc
 * @str: Array [línea actual, acumulador de todas las líneas]
 * @limit: Delimitador que termina el heredoc
 * 
 * Verifica si la línea es el delimitador. Si no lo es, añade '\n'
 * y la concatena al acumulador str[1].
 * 
 * Return: 1 si se encontró el delimitador, 0 si no
 */
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

/**
 * get_here_str - Lee líneas hasta encontrar el delimitador
 * @str: Array [línea actual, acumulador de todas las líneas]
 * @len: Longitud de la línea actual (no usado)
 * @limit: Delimitador que termina el heredoc (ej: "EOF")
 * @warn: Mensaje de warning si se llega a EOF sin delimitador
 * 
 * Lee líneas con readline hasta:
 * 1. Encontrar una línea igual al delimitador (limit)
 * 2. Recibir Ctrl+D (EOF) - muestra warning
 * 3. Recibir Ctrl+C (g_status = 130)
 * 
 * Return: String con todas las líneas concatenadas
 */
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

/**
 * get_here_doc - Implementa la funcionalidad de heredoc (<<)
 * @str: Array [línea actual, acumulador] (inicializar con NULL)
 * @aux: Array [delimitador, mensaje de warning]
 * 
 * Implementa el heredoc de bash. Proceso:
 * 1. Crea un pipe
 * 2. Lee líneas del usuario hasta encontrar el delimitador (get_here_str)
 * 3. Escribe todo el contenido en el extremo de escritura del pipe
 * 4. Cierra el extremo de escritura
 * 5. Retorna el extremo de lectura (para usarlo como infile)
 * 
 * Si el usuario presiona Ctrl+C durante la lectura (g_status = 130),
 * cierra el pipe y retorna -1 para cancelar el comando.
 * 
 * Return: File descriptor del pipe (lectura), -1 si error o Ctrl+C
 */
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
