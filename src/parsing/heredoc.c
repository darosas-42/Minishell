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
 * get_here_str - Lee líneas hasta encontrar el delimitador
 * @str: Array [línea actual, acumulador de todas las líneas]
 * @len: Longitud de la línea actual
 * @limit: Delimitador que termina el heredoc (ej: "EOF")
 * @warn: Mensaje de warning si se llega a EOF sin delimitador
 * 
 * Lee líneas con readline hasta:
 * 1. Encontrar una línea igual al delimitador (limit)
 * 2. Recibir Ctrl+D (EOF) - muestra warning
 * 3. Recibir Ctrl+C (g_status = 130)
 * 
 * Cada línea se acumula en str[1], añadiendo '\n' al final.
 * El prompt para heredoc es "> " (vs "$ " normal).
 * 
 * Return: String con todas las líneas concatenadas
 */
static char	*get_here_str(char *str[2], size_t len, char *limit, char *warn)
{
	char	*temp;

	while (g_status != 130 && (!str[0] || ft_strncmp(str[0], limit, len) \
		|| ft_strlen(limit) != len))
	{
		temp = str[1];
		str[1] = ft_strjoin(str[1], str[0]);
		free(temp);
		free(str[0]);
		str[0] = readline("> ");
		if (!str[0])
		{
			printf("%s (wanted `%s\')\n", warn, limit);
			break ;
		}
		temp = str[0];
		str[0] = ft_strjoin(str[0], "\n");
		free(temp);
		len = ft_strlen(str[0]) - 1;
	}
	free(str[0]);
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
