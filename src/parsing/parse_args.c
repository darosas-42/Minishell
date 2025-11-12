/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 12:08:12 by aperez-b          #+#    #+#             */
/*   Updated: 2022/03/07 21:26:20 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

/**
 * split_all - Expande variables y divide argumentos considerando operadores
 * @args: Array de argumentos a procesar
 * @prompt: Estructura con información del prompt (incluye envp para expansión)
 * 
 * Esta función realiza las siguientes operaciones en orden:
 * 1. Expande variables de entorno ($VAR, $?, $$)
 * 2. Expande el path del home (~)
 * 3. Divide el string en tokens separando operadores (<, |, >)
 * 
 * Return: Array de strings con argumentos expandidos y divididos
 */
static char	**filter_empty(char **args)
{
	char	**new;
	int		i;
	int		j;

	if (!args)
		return (NULL);
	new = malloc(sizeof(char *) * (matrixlen(args) + 1));
	if (!new)
		return (NULL);
	i = -1;
	j = 0;
	while (args[++i])
	{
		if (args[i][0])
			new[j++] = args[i];
		else
			free(args[i]);
	}
	new[j] = NULL;
	free(args);
	return (new);
}

static char	**split_all(char **args, t_prompt *prompt)
{
	char	**subsplit;
	int		i;
	int		quotes[2];

	i = -1;
	while (args && args[++i])
	{
		args[i] = expand_vars(args[i], -1, quotes, prompt);
		args[i] = expand_path(args[i], -1, quotes,
				ms_getenv("HOME", prompt->envp, 4));
		subsplit = ft_cmdsubsplit(args[i], "<|>");
		ft_matrix_replace_in(&args, subsplit, i);
		i += matrixlen(subsplit) - 1;
		free_matrix(subsplit);
	}
	return (filter_empty(args));
}

/**
 * parse_args - Parsea argumentos y ejecuta comandos
 * @args: Array de argumentos ya divididos
 * @p: Estructura del prompt con información del shell
 * 
 * Flujo de ejecución:
 * 1. Divide y expande todos los argumentos (split_all)
 * 2. Crea nodos de comandos con redirecciones (fill_nodes)
 * 3. Ejecuta los comandos o builtins (builtin)
 * 4. Espera a que terminen todos los procesos hijos
 * 5. Normaliza el código de salida (g_status)
 * 
 * Return: Puntero al prompt o NULL si se ejecutó exit
 */
static void	*parse_args(char **args, t_prompt *p)
{
	int	is_exit;
	int	i;

	is_exit = 0;
	p->cmds = fill_nodes(split_all(args, p), -1);
	if (!p->cmds)
		return (p);
	i = ft_lstsize(p->cmds);
	g_status = builtin(p, p->cmds, &is_exit);
	while (i-- > 0)
		waitpid(-1, &g_status, 0);
	if (!is_exit && g_status == 13)
		g_status = 0;
	if (g_status > 255)
		g_status = g_status / 255;
	if (args && is_exit)
	{
		ft_lstclear(&p->cmds, free_cmd);
		return (NULL);
	}
	return (p);
}

/**
 * check_args - Punto de entrada principal del parseo
 * @out: String de entrada leído por readline
 * @p: Estructura del prompt
 * 
 * Esta es la función principal que se llama desde el main después de
 * leer una línea con readline. Realiza:
 * 1. Verifica si hay input (Ctrl+D devuelve NULL)
 * 2. Añade la línea al historial si no está vacía
 * 3. Divide la línea en tokens respetando espacios y comillas (ft_cmdtrim)
 * 4. Llama a parse_args para procesar y ejecutar
 * 5. Actualiza la variable de entorno "_" con el último argumento
 * 6. Libera la memoria de los comandos
 * 
 * Return: Puntero al prompt si continúa, NULL si se debe salir, "" si error
 */
void	*check_args(char *out, t_prompt *p)
{
	char	**a;
	t_mini	*n;

	if (!out)
	{
		printf("exit\n");
		return (NULL);
	}
	if (out[0] != '\0')
		add_history(out);
	a = ft_cmdtrim(out, " ");
	free(out);
	if (!a)
		ms_perror(QUOTERROR, NULL, 1);
	if (!a)
		return ("");
	p = parse_args(a, p);
	if (p && p->cmds)
		n = p->cmds->content;
	if (p && p->cmds && n && n->full_cmd && ft_lstsize(p->cmds) == 1)
		p->envp = ms_setenv("_", n->full_cmd[matrixlen(n->full_cmd) - 1],
				p->envp, 1);
	if (p && p->cmds)
		ft_lstclear(&p->cmds, free_cmd);
	return (p);
}
