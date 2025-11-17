/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darosas- <darosas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:45:41 by darosas-          #+#    #+#             */
/*   Updated: 2025/11/17 18:45:41 by darosas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line_bonus.h"

# define FDREAD 0
# define FDWRITE 1

typedef struct s_prompt
{
	t_list	*cmds;
	char	**envp;
	pid_t	pid;
	int		e_status;
}		t_prompt;

typedef struct s_mini
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
}		t_mini;

enum	e_errors
{
	QUOTERROR = 1,
	NO_FL = 2,
	NO_PERM = 3,
	NO_CMD = 6,
	DUPERROR = 7,
	FORKERROR = 8,
	PIPERROR = 9,
	PIPENDERROR = 10,
	MEMORY = 11,
	IS_DIR = 12,
	ISNOT_DIR = 13,
	EXPORT_ERROR = 14
};

// Common functions

char	**ms_setenv(char *var, char *str, char **envp, int i);
char	*ms_getenv(char *var, char **envp, int i);
void	signal_sigint(int sig);
void	signals_interactive(t_prompt *prompt);
void	signals_not_interactive(void);
void	signals_default(void);
char	**enlarge_matrix(char **matrix, char *str);
char	**matrix_dup(char **matrix);
void	free_matrix(char **matrix);
int		matrixlen(char **matrix);
int		strchr_index(const char *s, int c);
int		ft_strchars_i(const char *s, const char *set);
void	free_cmd(void *content);
void	ft_matrix_replace_in(char ***m, char **replacement, int pos);
int		is_valid_var_name(char *var);
char	**bubble_sort(char **matrix);
char	*get_prompt(t_prompt prompt);
void	*ms_perror(t_prompt *prompt, int err_type, char *param, int err);

// Parsing

char	*expand_vars(char *str, int i, int quotes[2], t_prompt *prompt);
char	*expand_path(char *str, int i, int quotes[2], char *var);
t_list	*fill_nodes(char **args, int i);
char	**ft_cmdsubsplit(char const *s, char *set);
char	**ft_cmdtrim(char const *s, char *set);
char	*ft_strtrim_all(char const *s1, int squote, int dquote);
t_mini	*get_infile2(t_mini *node, char **args, int *i);
t_mini	*get_infile1(t_mini *node, char **args, int *i);
t_mini	*get_outfile2(t_mini *node, char **args, int *i);
t_mini	*get_outfile1(t_mini *node, char **args, int *i);
int		get_fd(int oldfd, char *path, int flags[2]);
int		get_here_doc(char *str[2], char *aux[2]);
void	*check_args(char *out, t_prompt *p);

// Execution

void	get_full_path(t_prompt *prompt, t_list *cmd, DIR *dir);
int		fork_cmd(t_prompt *prompt, t_list *cmd, int fd[2]);
int		builtin(t_prompt *prompt, t_list *cmd, int *is_exit);
int		is_builtin(t_mini *node);
int		ms_echo(t_list *cmd);
int		ms_env(t_prompt *prompt);
int		ms_pwd(void);
void	*cmd_others(t_prompt *prompt, t_list *cmd);
void	export_error(t_prompt *prompt, char *param, int err);
int		ms_export(t_prompt *prompt);
int		ms_unset(t_prompt *prompt);
int		ms_exit(t_list *cmd, int *is_exit);
int		ms_cd(t_prompt *prompt);

#endif