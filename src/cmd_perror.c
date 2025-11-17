/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_perror.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darosas- <darosas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 21:05:04 by dreix             #+#    #+#             */
/*   Updated: 2025/11/17 18:46:15 by darosas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static void	aux_msperror(char *param)
{
	ft_putstr_fd("minishell: ", 2);
	if (param)
	{
		ft_putstr_fd(param, 2);
		ft_putstr_fd(": ", 2);
	}
}

void	export_error(char *param, int err)
{
	g_status = err;
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(param, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	*ms_perror(int err_type, char *param, int err)
{
	g_status = err;
	aux_msperror(param);
	if (err_type == QUOTERROR)
		ft_putendl_fd("error while looking for matching quote", 2);
	else if (err_type == NO_FL)
		ft_putendl_fd("No such file or directory", 2);
	else if (err_type == NO_PERM)
		ft_putendl_fd("Permission denied", 2);
	else if (err_type == NO_CMD)
		ft_putendl_fd("command not found", 2);
	else if (err_type == DUPERROR)
		ft_putendl_fd("dup2 failed", 2);
	else if (err_type == FORKERROR)
		ft_putendl_fd("fork failed", 2);
	else if (err_type == PIPERROR)
		ft_putendl_fd("error creating pipe", 2);
	else if (err_type == PIPENDERROR)
		ft_putendl_fd("syntax error near unexpected token `|'", 2);
	else if (err_type == MEMORY)
		ft_putendl_fd("no memory left on device", 2);
	else if (err_type == IS_DIR)
		ft_putendl_fd("Is a directory", 2);
	else if (err_type == ISNOT_DIR)
		ft_putendl_fd("Not a directory", 2);
	return (NULL);
}
