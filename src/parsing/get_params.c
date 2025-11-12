/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:48:14 by aperez-b          #+#    #+#             */
/*   Updated: 2022/03/07 21:21:29 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

/**
 * get_fd - Abre un archivo y retorna su file descriptor
 * @oldfd: File descriptor anterior (para cerrar si es necesario)
 * @path: Ruta del archivo a abrir
 * @flags: Array [es_escritura, es_append]
 *   flags[0] = 1: Escritura, 0: Lectura
 *   flags[1] = 1: Append (>>), 0: Truncate (>)
 * 
 * Cierra el fd anterior si existe (> 2), verifica permisos y abre el archivo.
 * Modos de apertura:
 * - Lectura: O_RDONLY (para <)
 * - Escritura truncate: O_CREAT | O_WRONLY | O_TRUNC (para >)
 * - Escritura append: O_CREAT | O_WRONLY | O_APPEND (para >>)
 * 
 * Muestra errores si el archivo no existe o no hay permisos.
 * 
 * Return: Nuevo fd, o -1 si error
 */
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

/**
 * get_outfile1 - Procesa redirección de salida simple (>)
 * @node: Nodo de comando actual
 * @args: Array de argumentos
 * @i: Puntero al índice actual (se incrementa)
 * 
 * Maneja la redirección ">". El siguiente argumento debe ser el nombre del archivo.
 * 
 * Ejemplo: echo hello > file.txt
 *   - args[i] = ">"
 *   - args[i+1] = "file.txt"
 * 
 * El archivo se crea si no existe, o se trunca si existe.
 * Si hay error (no hay archivo después de > o falla al abrir), pone i = -1.
 * 
 * Return: Nodo con outfile actualizado
 */
t_mini	*get_outfile1(t_mini *node, char **args, int *i)
{
	char	*nl;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 0;
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[*i])
		node->outfile = get_fd(node->outfile, args[*i], flags);
	if (!args[*i] || node->outfile == -1)
	{
		*i = -1;
		if (node->outfile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (node);
}

/**
 * get_outfile2 - Procesa redirección de salida append (>>)
 * @node: Nodo de comando actual
 * @args: Array de argumentos
 * @i: Puntero al índice actual (se incrementa dos veces: > y >)
 * 
 * Maneja la redirección ">>". Similar a get_outfile1 pero en modo append.
 * 
 * Ejemplo: echo hello >> file.txt
 *   - args[i] = ">"
 *   - args[i+1] = ">"
 *   - args[i+2] = "file.txt"
 * 
 * El archivo se crea si no existe, o se añade al final si existe.
 * Incrementa i dos veces para saltar ambos '>'.
 * 
 * Return: Nodo con outfile actualizado en modo append
 */
t_mini	*get_outfile2(t_mini *node, char **args, int *i)
{
	char	*nl;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 1;
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[++(*i)])
		node->outfile = get_fd(node->outfile, args[*i], flags);
	if (!args[*i] || node->outfile == -1)
	{
		*i = -1;
		if (node->outfile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (node);
}

/**
 * get_infile1 - Procesa redirección de entrada (<)
 * @node: Nodo de comando actual
 * @args: Array de argumentos
 * @i: Puntero al índice actual (se incrementa)
 * 
 * Maneja la redirección "<". Lee desde un archivo existente.
 * 
 * Ejemplo: cat < file.txt
 *   - args[i] = "<"
 *   - args[i+1] = "file.txt"
 * 
 * El archivo debe existir y tener permisos de lectura.
 * Si falla, muestra error apropiado (no existe o sin permisos).
 * 
 * Return: Nodo con infile actualizado
 */
t_mini	*get_infile1(t_mini *node, char **args, int *i)
{
	char	*nl;
	int		flags[2];

	flags[0] = 0;
	flags[1] = 0;
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[*i])
		node->infile = get_fd(node->infile, args[*i], flags);
	if (!args[*i] || node->infile == -1)
	{
		*i = -1;
		if (node->infile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (node);
}

/**
 * get_infile2 - Procesa here document (<<)
 * @node: Nodo de comando actual
 * @args: Array de argumentos
 * @i: Puntero al índice actual (se incrementa dos veces)
 * 
 * Maneja el here document "<<". Lee input del usuario hasta encontrar
 * el delimitador especificado.
 * 
 * Ejemplo: cat << EOF
 *   - args[i] = "<"
 *   - args[i+1] = "<"
 *   - args[i+2] = "EOF"
 *   Luego lee líneas hasta encontrar "EOF"
 * 
 * Llama a get_here_doc que:
 * 1. Lee líneas con readline hasta encontrar el delimitador
 * 2. Crea un pipe y escribe todo el input en él
 * 3. Retorna el fd de lectura del pipe
 * 
 * Return: Nodo con infile actualizado (fd del pipe con el heredoc)
 */
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
