/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreix <darosas-@student.42malaga.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:17:34 by dreix             #+#    #+#             */
/*   Updated: 2025/10/25 04:26:19 by dreix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static void	ms_getpid(t_prompt *prompt)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ms_error(FORKERROR, NULL, 1);
		free_matrix(&prompt->envp);
		exit(1);
	}
	if (pid == 0)
	{
		free_matrix(&prompt->envp);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	prompt->pid = pid - 1;
}

char	**ms_setvar(char *var, char *str, char **envp, int i)
{
	char	*new[2];
	int		j;
	int		k;

	new[0] = ft_strjoin(var, '=');
	new[1] = ft_strjoin(new, var);
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

char	*ms_getvar(char *var, char **envp, int i)
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

static t_prompt	init_var(t_prompt prompt, char *argv)
{
	char	*str;
	char	*n;

	str = getcwd(NULL, 0);
	prompt.envp = ms_setvar("PWD", str, prompt.envp, 3);
	free(str);
	str = ms_getvar("SHLVL", prompt.envp, 5);
	if (!str || ft_atoi(str) <= 0)
		n = ft_strdup("1");
	else
		n = ft_itoa(ft_atoi(str) + 1);
	prompt.envp = ms_setvar("SHLVL", n, prompt.envp, 5);
	free(n);
	free(str);
	str = ms_getvar("PATH", prompt.envp, 4);
	if (!str)
		prompt.envp = mini_setvar("PATH", \
		"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", prompt.envp, 4);
	free(str);
	str = ms_getvar("_", prompt.envp, 1);
	if (!str)
		prompt.envp = ms_setvar("_", argv, prompt.envp, 1);
	free(str);
	return (prompt);	
}

static t_prompt init_struct(char **argv, char **envp)
{
	t_prompt	prompt;
	
	g_status = 0;
	prompt.cmds = NULL;
	prompt.envp = matrix_dup(envp);
	if (!prompt.envp)
	{
		mini_perror(MEMORY, NULL, 1);
		exit(1);
	}
	ms_getpid(&prompt);
	prompt = init_var(prompt, argv[0]);
	return (prompt);
}

int	main(int argc, char **argv, char **envp)
{
	t_prompt	prompt;

	prompt = init_struct(argv, envp);
	while (argc)
	{
		
	}
}
