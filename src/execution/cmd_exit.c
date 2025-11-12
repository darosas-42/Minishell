/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darosas- <darosas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:59:17 by dreix             #+#    #+#             */
/*   Updated: 2025/11/12 20:38:47 by darosas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v')
		return (1);
	return (0);
}

static int	ms_atoi_nb_checker(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && !ms_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	ms_atoi_check(char *str, long *n)
{
	int	i;
	int	neg;

	i = 0;
	*n = 0;
	neg = 1;
	while (ms_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	if (!ms_atoi_nb_checker(&str[i]))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		*n = (*n * 10) + (str[i] - '0');
		i++;
	}
	*n = *n * neg;
	return (1);
}

int	ms_exit(t_list *cmd, int *is_exit)
{
	t_mini	*ptr;
	long	result;

	ptr = cmd->content;
	*is_exit = !cmd->next;
	if (*is_exit)
		ft_putstr_fd("exit\n", 2);
	if (!ptr->full_cmd[1])
		return (0);
	if (!ms_atoi_check(ptr->full_cmd[1], &result))
	{
		ft_putstr_fd("minishell: exit:", 2);
		ft_putstr_fd(ptr->full_cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (2);
	}
	else if (ptr->full_cmd[2])
	{
		*is_exit = 0;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	result %= 256 + 256 * (result < 0);
	return (result);
}
