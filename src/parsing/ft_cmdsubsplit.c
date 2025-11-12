/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdsubsplit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 18:23:56 by aperez-b          #+#    #+#             */
/*   Updated: 2022/03/08 12:39:24 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * ft_count_words - Cuenta tokens incluyendo los separadores
 * @s: String a analizar
 * @set: Caracteres separadores especiales (ej: "<|>")
 * @count: Contador inicial
 * 
 * A diferencia de ft_cmdtrim, esta función cuenta CADA token,
 * incluyendo los separadores. Por ejemplo:
 * "cat<file" se divide en ["cat", "<", "file"] = 3 palabras
 * 
 * Los separadores se incluyen como tokens individuales SOLO si
 * no están dentro de comillas.
 * 
 * Return: Número total de tokens, -1 si hay comillas sin cerrar
 */
static int	ft_count_words(char *s, char *set, int count)
{
	int		q[2];
	int		i;

	i = 0;
	q[0] = 0;
	q[1] = 0;
	while (s && s[i] != '\0')
	{
		count++;
		if (!ft_strchr(set, s[i]))
		{
			while ((!ft_strchr(set, s[i]) || q[0] || q[1]) && s[i] != '\0')
			{
				q[0] = (q[0] + (!q[1] && s[i] == '\'')) % 2;
				q[1] = (q[1] + (!q[0] && s[i] == '\"')) % 2;
				i++;
			}
			if (q[0] || q[1])
				return (-1);
		}
		else
			i++;
	}
	return (count);
}

/**
 * ft_fill_array - Extrae tokens separando operadores
 * @aux: Array destino para los tokens
 * @s: String fuente
 * @set: Caracteres operadores a separar
 * @i: Array [índice actual, inicio token, índice destino]
 * 
 * Separa cada token del string. Los operadores (<, |, >) se extraen
 * como tokens individuales. Por ejemplo:
 * 
 * Input:  "cat<file|grep test"
 * Output: ["cat", "<", "file", "|", "grep test", NULL]
 * 
 * Los operadores dentro de comillas NO se separan.
 * 
 * Return: Array con todos los tokens
 */
static char	**ft_fill_array(char **aux, char *s, char *set, int i[3])
{
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	while (s && s[i[0]] != '\0')
	{
		i[1] = i[0];
		if (!ft_strchr(set, s[i[0]]))
		{
			while ((!ft_strchr(set, s[i[0]]) || q[0] || q[1]) && s[i[0]])
			{
				q[0] = (q[0] + (!q[1] && s[i[0]] == '\'')) % 2;
				q[1] = (q[1] + (!q[0] && s[i[0]] == '\"')) % 2;
				i[0]++;
			}
		}
		else
			i[0]++;
		aux[i[2]++] = ft_substr(s, i[1], i[0] - i[1]);
	}
	return (aux);
}

/**
 * ft_cmdsubsplit - Divide string separando operadores de redirección/pipe
 * @s: String a dividir
 * @set: String con operadores a separar (típicamente "<|>")
 * 
 * Esta función es clave para el parseo. Separa los operadores de shell
 * como tokens independientes, pero SOLO si no están dentro de comillas.
 * 
 * Ejemplo de uso en split_all():
 * Input:  "echo hello>file"
 * Output: ["echo hello", ">", "file", NULL]
 * 
 * Esto permite después identificar fácilmente redirecciones y pipes.
 * 
 * Return: Array de tokens, NULL si error o comillas sin cerrar
 */
char	**ft_cmdsubsplit(char const *s, char *set)
{
	char	**aux;
	int		nwords;
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if (!s)
		return (NULL);
	nwords = ft_count_words((char *)s, set, 0);
	if (nwords == -1)
		return (NULL);
	aux = malloc((nwords + 1) * sizeof(char *));
	if (aux == NULL)
		return (NULL);
	aux = ft_fill_array(aux, (char *)s, set, i);
	aux[nwords] = NULL;
	return (aux);
}
