/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbueno-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:17:55 by mbueno-g          #+#    #+#             */
/*   Updated: 2022/03/07 21:12:34 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

/**
 * expand_path - Expande el símbolo ~ al directorio HOME
 * @str: String que puede contener ~
 * @i: Índice inicial (usar -1)
 * @quotes: Array para track de comillas [simple, doble] (usar {0,0})
 * @var: Valor de la variable HOME
 * 
 * Reemplaza ~ por el valor de $HOME, pero SOLO si:
 * - No está dentro de comillas simples
 * - No está precedido por $ (para evitar expandir $~)
 * - Está al inicio o después de espacio
 * 
 * Ejemplo: ~/Documents -> /home/user/Documents
 * 
 * Usa recursión para manejar múltiples ~ en el mismo string.
 * Libera var al final.
 * 
 * Return: Nuevo string con ~ expandido
 */
char	*expand_path(char *str, int i, int quotes[2], char *var)
{
	char	*path;
	char	*aux;

	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2;
		if (!quotes[0] && !quotes[1] && str[i] == '~' && (i == 0 || \
			str[i - 1] != '$'))
		{
			aux = ft_substr(str, 0, i);
			path = ft_strjoin(aux, var);
			free(aux);
			aux = ft_substr(str, i + 1, ft_strlen(str));
			free(str);
			str = ft_strjoin(path, aux);
			free(aux);
			free(path);
			return (expand_path(str, i + ft_strlen(var) - 1, quotes, var));
		}
	}
	free(var);
	return (str);
}

/**
 * get_substr_var - Extrae y expande una variable de entorno
 * @str: String que contiene la variable
 * @i: Posición del nombre de la variable (después del $)
 * @prompt: Estructura con envp para buscar variables
 * 
 * Extrae una variable del string y la reemplaza por su valor.
 * Maneja casos especiales:
 * - $VAR: Variable de entorno normal
 * - $$: PID del shell (prompt->pid)
 * - $?: Código de salida del último comando (g_status)
 * 
 * Ejemplo: "echo $USER" -> "echo pablo"
 * 
 * La variable se busca hasta encontrar un delimitador (espacio, |, >, <, etc).
 * 
 * Return: Nuevo string con la variable expandida
 */
static char	*get_substr_var(char *str, int i, t_prompt *prompt)
{
	char	*aux;
	int		pos;
	char	*path;
	char	*var;

	pos = ft_strchars_i(&str[i], "|\"\'$?>< ") + (ft_strchr("$?", str[i]) != 0);
	if (pos == -1)
		pos = ft_strlen(str) - 1;
	aux = ft_substr(str, 0, i - 1);
	var = ms_getenv(&str[i], prompt->envp, ft_strchars_i(&str[i], "\"\'$|>< "));
	if (!var && str[i] == '$')
		var = ft_itoa(prompt->pid);
	else if (!var && str[i] == '?')
		var = ft_itoa(g_status);
	path = ft_strjoin(aux, var);
	free(aux);
	aux = ft_strjoin(path, &str[i + pos]);
	free(var);
	free(path);
	free(str);
	return (aux);
}

/**
 * expand_vars - Expande todas las variables de entorno en un string
 * @str: String que puede contener variables ($VAR, $?, $$)
 * @i: Índice inicial (usar -1)
 * @quotes: Array para track de comillas (usar array con {0,0})
 * @prompt: Estructura con envp
 * 
 * Busca y expande todas las variables de entorno en el string.
 * Reglas de expansión:
 * - NO expande dentro de comillas simples: '$USER' -> $USER
 * - SÍ expande dentro de comillas dobles: "$USER" -> pablo
 * - Variables válidas: letras, números, _, y caracteres especiales como ? y $
 * 
 * Usa recursión para expandir múltiples variables.
 * Llama a get_substr_var para cada variable encontrada.
 * 
 * Return: String con todas las variables expandidas
 */
char	*expand_vars(char *str, int i, int quotes[2], t_prompt *prompt)
{
	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2;
		if (!quotes[0] && str[i] == '$' && str[i + 1] && \
			((ft_strchars_i(&str[i + 1], "/~%^{}:; ") && !quotes[1]) || \
			(ft_strchars_i(&str[i + 1], "/~%^{}:;\"") && quotes[1])))
			return (expand_vars(get_substr_var(str, ++i, prompt), -1, \
				quotes, prompt));
	}
	return (str);
}
