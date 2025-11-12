/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbueno-g <mbueno-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:05:01 by aperez-b          #+#    #+#             */
/*   Updated: 2022/03/07 21:20:17 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * mini_init - Inicializa una estructura de comando
 * 
 * Crea y inicializa un nodo t_mini que representa un comando individual.
 * Valores iniciales:
 * - full_cmd: NULL (se llenará con el comando y argumentos)
 * - full_path: NULL (se llenará con el path completo del ejecutable)
 * - infile: STDIN_FILENO (fd 0, entrada estándar)
 * - outfile: STDOUT_FILENO (fd 1, salida estándar)
 * 
 * Return: Puntero a nueva estructura t_mini, NULL si falla malloc
 */
static t_mini	*mini_init(void)
{
	t_mini	*mini;

	mini = malloc(sizeof(t_mini));
	if (!mini)
		return (NULL);
	mini->full_cmd = NULL;
	mini->full_path = NULL;
	mini->infile = STDIN_FILENO;
	mini->outfile = STDOUT_FILENO;
	return (mini);
}

/**
 * get_params - Procesa un token y actualiza el nodo de comando
 * @node: Nodo de comando actual
 * @a: Array [args originales, args sin comillas]
 * @i: Puntero al índice actual
 * 
 * Analiza cada token y realiza la acción correspondiente:
 * - ">>": Redirección append (get_outfile2)
 * - ">": Redirección salida (get_outfile1)
 * - "<<": Here document (get_infile2)
 * - "<": Redirección entrada (get_infile1)
 * - "|": Error si está mal colocado (sintaxis)
 * - Otro: Se añade a full_cmd (comando o argumento)
 * 
 * Modifica *i según el tipo de redirección procesada.
 * Si hay error, pone *i = -2 para señalizar.
 * 
 * Return: Nodo actualizado con el parámetro procesado
 */
static t_mini	*get_params(t_mini *node, char **a[2], int *i)
{
	if (a[0][*i])
	{
		if (a[0][*i][0] == '>' && a[0][*i + 1] && a[0][*i + 1][0] == '>')
			node = get_outfile2(node, a[1], i);
		else if (a[0][*i][0] == '>')
			node = get_outfile1(node, a[1], i);
		else if (a[0][*i][0] == '<' && a[0][*i + 1] && \
			a[0][*i + 1][0] == '<')
			node = get_infile2(node, a[1], i);
		else if (a[0][*i][0] == '<')
			node = get_infile1(node, a[1], i);
		else if (a[0][*i][0] != '|')
			node->full_cmd = enlarge_matrix(node->full_cmd, a[1][*i]);
		else
		{
			ms_perror(PIPERROR, NULL, 2);
			*i = -2;
		}
		return (node);
	}
	ms_perror(PIPERROR, NULL, 2);
	*i = -2;
	return (node);
}

/**
 * get_trimmed - Crea copia de args sin comillas
 * @args: Array de argumentos con comillas
 * 
 * Duplica el array de argumentos y elimina todas las comillas
 * de cada string usando ft_strtrim_all. Esto es necesario porque
 * necesitamos dos versiones:
 * - args: Versión original para detectar operadores
 * - temp: Versión limpia para usar como argumentos reales
 * 
 * Ejemplo:
 * Input:  ["echo", "\"hello\"", NULL]
 * Output: ["echo", "hello", NULL]
 * 
 * Return: Nuevo array con strings sin comillas
 */
static char	**get_trimmed(char **args)
{
	char	**temp;
	char	*aux;
	int		j;

	j = -1;
	temp = matrix_dup(args);
	while (temp && temp[++j])
	{
		aux = ft_strtrim_all(temp[j], 0, 0);
		free(temp[j]);
		temp[j] = aux;
	}
	return (temp);
}

/**
 * stop_fill - Limpia memoria y retorna NULL en caso de error
 * @cmds: Lista de comandos a liberar
 * @args: Array original a liberar
 * @temp: Array de argumentos limpios a liberar
 * 
 * Función helper para manejar errores durante el parseo.
 * Libera toda la memoria alocada y retorna NULL para señalizar error.
 * 
 * Return: NULL siempre
 */
static t_list	*stop_fill(t_list *cmds, char **args, char **temp)
{
	ft_lstclear(&cmds, free_cmd);
	free_matrix(temp);
	free_matrix(args);
	return (NULL);
}

/**
 * fill_nodes - Crea lista de nodos de comandos desde argumentos parseados
 * @args: Array de tokens (comandos, argumentos, operadores)
 * @i: Índice inicial (usar -1)
 * 
 * Esta es la función principal del parseo final. Crea una lista enlazada
 * donde cada nodo representa un comando con sus redirecciones.
 * 
 * Proceso:
 * 1. Crea versión sin comillas de args (get_trimmed)
 * 2. Crea nodo nuevo al inicio o después de cada '|'
 * 3. Procesa cada token con get_params (redirecciones o argumentos)
 * 4. Maneja errores (pipes mal colocados, sintaxis)
 * 
 * Ejemplo:
 * Input: ["cat", "<", "file", "|", "grep", "test", NULL]
 * Output: Lista con 2 nodos:
 *   - Nodo 1: cmd="cat", infile=file
 *   - Nodo 2: cmd="grep test"
 * 
 * Return: Lista de comandos (t_list de t_mini), NULL si error
 */
t_list	*fill_nodes(char **args, int i)
{
	t_list	*cmds[2];
	char	**temp[2];

	cmds[0] = NULL;
	temp[1] = get_trimmed(args);
	while (args[++i])
	{
		cmds[1] = ft_lstlast(cmds[0]);
		if (i == 0 || (args[i][0] == '|' && args[i + 1] && args[i + 1][0]))
		{
			i += args[i][0] == '|';
			ft_lstadd_back(&cmds[0], ft_lstnew(mini_init()));
			cmds[1] = ft_lstlast(cmds[0]);
		}
		temp[0] = args;
		cmds[1]->content = get_params(cmds[1]->content, temp, &i);
		if (i < 0)
			return (stop_fill(cmds[0], args, temp[1]));
		if (!args[i])
			break ;
	}
	free_matrix(temp[1]);
	free_matrix(args);
	return (cmds[0]);
}
