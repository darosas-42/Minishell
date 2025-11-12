/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 20:59:58 by aperez-b          #+#    #+#             */
/*   Updated: 2021/11/03 10:11:27 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * malloc_len - Calcula cuántas comillas hay que eliminar
 * @s1: String a analizar
 * 
 * Cuenta cuántas comillas (simples y dobles) hay en el string que
 * deben eliminarse. Solo cuenta las comillas que están correctamente
 * balanceadas (no las que están dentro de otro tipo de comilla).
 * 
 * Ejemplo: "hola 'mundo'" tiene 4 comillas a eliminar
 *          'it\'s' tendría error (comilla simple sin cerrar)
 * 
 * Return: Número de comillas a eliminar, -1 si hay comillas sin cerrar
 */
static int	malloc_len(char const *s1)
{
	int	count;
	int	i;
	int	dquote;
	int	squote;

	i = 0;
	count = 0;
	dquote = 0;
	squote = 0;
	while (s1 && s1[i])
	{
		squote = (squote + (!dquote && s1[i] == '\'')) % 2;
		dquote = (dquote + (!squote && s1[i] == '\"')) % 2;
		if ((s1[i] == '\"' && !squote) || (s1[i] == '\'' && !dquote))
			count++;
		i++;
	}
	if (squote || dquote)
		return (-1);
	return (count);
}

/**
 * ft_strtrim_all - Elimina todas las comillas de un string
 * @s1: String del que eliminar comillas
 * @squote: Estado inicial de comilla simple (usar 0)
 * @dquote: Estado inicial de comilla doble (usar 0)
 * 
 * Elimina las comillas externas de un string, dejando el contenido
 * sin comillas. Se usa después de dividir los argumentos para limpiarlos.
 * 
 * Ejemplos:
 * Input:  "hello world"  -> Output: hello world
 * Input:  'test'         -> Output: test
 * Input:  "it's ok"      -> Output: it's ok
 * 
 * Las comillas dentro de otras comillas se preservan como caracteres.
 * 
 * Return: Nuevo string sin comillas, NULL si error o comillas sin cerrar
 */
char	*ft_strtrim_all(char const *s1, int squote, int dquote)
{
	int		count;
	int		i[2];
	char	*trimmed;

	i[1] = -1;
	i[0] = 0;
	count = malloc_len(s1);
	if (!s1 || count == -1)
		return (NULL);
	trimmed = malloc(sizeof(char) * (ft_strlen(s1) - count + 1));
	if (!trimmed)
		return (NULL);
	while (s1[i[0]])
	{
		squote = (squote + (!dquote && s1[i[0]] == '\'')) % 2;
		dquote = (dquote + (!squote && s1[i[0]] == '\"')) % 2;
		if ((s1[i[0]] != '\"' || squote) && (s1[i[0]] != '\'' || dquote)
			&& ++i[1] >= 0)
			trimmed[i[1]] = s1[i[0]];
		i[0]++;
	}
	trimmed[++i[1]] = '\0';
	return (trimmed);
}
