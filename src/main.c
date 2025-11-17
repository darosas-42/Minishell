/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darosas- <darosas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:17:34 by dreix             #+#    #+#             */
/*   Updated: 2025/11/17 19:22:29 by darosas-         ###   ########.fr       */
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
		ms_perror(prompt, FORKERROR, NULL, 1);
		free_matrix(prompt->envp);
		exit(1);
	}
	if (!pid)
	{
		free_matrix(prompt->envp);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	prompt->pid = pid - 1;
}

static t_prompt	init_envp(t_prompt prompt, char *argv)
{
	char	*str;
	char	*n;

	str = getcwd(NULL, 0);
	prompt.envp = ms_setenv("PWD", str, prompt.envp, 3);
	free(str);
	str = ms_getenv("SHLVL", prompt.envp, 5);
	if (!str || ft_atoi(str) <= 0)
		n = ft_strdup("1");
	else
		n = ft_itoa(ft_atoi(str) + 1);
	prompt.envp = ms_setenv("SHLVL", n, prompt.envp, 5);
	free(n);
	free(str);
	str = ms_getenv("PATH", prompt.envp, 4);
	if (!str)
		prompt.envp = ms_setenv("PATH", \
"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", prompt.envp, 4);
	free(str);
	str = ms_getenv("_", prompt.envp, 1);
	if (!str)
		prompt.envp = ms_setenv("_", argv, prompt.envp, 1);
	free(str);
	return (prompt);
}

static t_prompt	init_struct(char **argv, char **envp)
{
	t_prompt	prompt;

	g_status = 0;
	prompt.e_status = 0;
	prompt.cmds = NULL;
	prompt.envp = matrix_dup(envp);
	if (!prompt.envp)
	{
		ms_perror(&prompt, MEMORY, NULL, 1);
		exit(1);
	}
	ms_getpid(&prompt);
	prompt = init_envp(prompt, argv[0]);
	return (prompt);
}

int	main(int argc, char **argv, char **envp)
{
	t_prompt	prompt;
	char		*path;
	char		*str;

	prompt = init_struct(argv, envp);
	while (argc)
	{
		signals_interactive(&prompt);
		path = get_prompt(prompt);
		if (!path)
			str = readline("guest@minishell:$ ");
		else
			str = readline(path);
		free(path);
		if (!check_args(str, &prompt))
			break ;
	}
	free_matrix(prompt.envp);
	return (prompt.e_status);
}
