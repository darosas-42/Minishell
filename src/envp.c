/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreix <darosas-@student.42malaga.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 21:16:20 by dreix             #+#    #+#             */
/*   Updated: 2025/10/27 20:07:08 by dreix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ms_setenv(char *var, char *str, char **envp, int i)
{
	char	*new[2];
	int		j;
	int		k;

	new[0] = ft_strjoin(var, "=");
	new[1] = ft_strjoin(new[0], str);
	free(new[0]);
	j = -1;
	while (!ft_strchr(var, '=') && envp && envp[++j])
	{
		k = i;
		if (k < strchr_index(envp[j], '='))
			k = strchr_index(envp[j], '=');
		if (!ft_strncmp(envp[j], var, k))
		{
			new[0] = envp[j];
			envp[j] = new[1];
			free(new[0]);
			return (envp);
		}
	}
	envp = enlarge_matrix(envp, new[1]);
	free(new[1]);
	return (envp);
}

char	*ms_getenv(char *var, char **envp, int i)
{
	int		j;
	int		k;
	char	*str;

	j = -1;
	while (!ft_strchr(var, '=') && envp && envp[++j])
	{
		k = i;
		if (k < strchr_index(envp[j], '='))
			k = strchr_index(envp[j], '=');
		if (!ft_strncmp(envp[j], var, k))
		{
			str = ft_substr(envp[j], k + 1, ft_strlen(envp[j]));
			return (str);
		}
	}
	return (NULL);
}
