/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 15:28:36 by aperez-b          #+#    #+#             */
/*   Updated: 2021/11/13 13:09:37 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * ft_count_words - Cuenta palabras respetando comillas
 * @s: String a analizar
 * @c: Caracteres delimitadores (ej: espacios)
 * @i: Array con [índice actual, contador de palabras]
 * 
 * Esta función cuenta cuántas palabras hay en el string considerando
 * que las comillas (simples y dobles) agrupan palabras aunque tengan
 * espacios. Por ejemplo: echo "hola mundo" cuenta como 2 palabras.
 * 
 * q[0]: indica si estamos dentro de comillas
 * q[1]: guarda el tipo de comilla que abrió (para cerrar la correcta)
 * 
 * Return: Número de palabras, o -1 si hay comillas sin cerrar
 */
static int	ft_count_words(const char *s, char *c, int i[2])
{
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	while (s[i[0]] != '\0')
	{
		if (!ft_strchr(c, s[i[0]]))
		{
			i[1]++;
			while ((!ft_strchr(c, s[i[0]]) || q[0]) && s[i[0]] != '\0')
			{
				if (!q[1] && (s[i[0]] == '\"' || s[i[0]] == '\''))
					q[1] = s[i[0]];
				q[0] = (q[0] + (s[i[0]] == q[1])) % 2;
				q[1] *= q[0] != 0;
				i[0]++;
			}
			if (q[0])
				return (-1);
		}
		else
			i[0]++;
	}
	return (i[1]);
}

/**
 * ft_fill_array - Extrae palabras del string respetando comillas
 * @aux: Array donde guardar las palabras extraídas
 * @s: String fuente
 * @set: Caracteres delimitadores
 * @i: Array [índice actual, inicio palabra, índice destino]
 * 
 * Extrae cada palabra del string y la guarda en el array. Las palabras
 * pueden contener espacios si están entre comillas. Las comillas se
 * mantienen en esta etapa (se eliminan después con ft_strtrim_all).
 * 
 * q[0]: track de comilla simple activa
 * q[1]: track de comilla doble activa
 * 
 * Return: Array rellenado con las palabras
 */
static char	**ft_fill_array(char **aux, char const *s, char *set, int i[3])
{
	int		s_len;
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	s_len = ft_strlen(s);
	while (s[i[0]])
	{
		while (ft_strchr(set, s[i[0]]) && s[i[0]] != '\0')
			i[0]++;
		i[1] = i[0];
		while ((!ft_strchr(set, s[i[0]]) || q[0] || q[1]) && s[i[0]])
		{
			q[0] = (q[0] + (!q[1] && s[i[0]] == '\'')) % 2;
			q[1] = (q[1] + (!q[0] && s[i[0]] == '\"')) % 2;
			i[0]++;
		}
		if (i[1] >= s_len)
			aux[i[2]++] = "\0";
		else
			aux[i[2]++] = ft_substr(s, i[1], i[0] - i[1]);
	}
	return (aux);
}

/**
 * ft_cmdtrim - Divide string en palabras respetando comillas
 * @s: String a dividir
 * @set: Caracteres delimitadores (normalmente espacios)
 * 
 * Similar a ft_split pero respeta comillas. Los espacios dentro de
 * comillas no separan palabras. Ejemplo:
 * 
 * Input:  echo "hello world" test
 * Output: ["echo", "\"hello world\"", "test", NULL]
 * 
 * Las comillas se mantienen y se eliminan después en fill_nodes.
 * 
 * Return: Array de strings con las palabras, NULL si error o comillas sin cerrar
 */
char	**ft_cmdtrim(char const *s, char *set)
{
	char	**aux;
	int		nwords;
	int		i[3];
	int		counts[2];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	counts[0] = 0;
	counts[1] = 0;
	if (!s)
		return (NULL);
	nwords = ft_count_words(s, set, counts);
	if (nwords == -1)
		return (NULL);
	aux = malloc((nwords + 1) * sizeof(char *));
	if (aux == NULL)
		return (NULL);
	aux = ft_fill_array(aux, s, set, i);
	aux[nwords] = NULL;
	return (aux);
}
