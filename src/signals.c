/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreix <darosas-@student.42malaga.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:33:12 by dreix             #+#    #+#             */
/*   Updated: 2025/10/27 19:02:40 by dreix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

void	signal_sigint(int sig)
{
	(void)sig;
	g_status = 130;
	rl_replace_line("", 0);
	rl_on_new_line();
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

void	signals_interactive(void)
{
	signal(SIGINT, signal_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_not_interactive(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
