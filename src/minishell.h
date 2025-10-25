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
# include "libft.h"

typedef struct s_prompt
{
	t_list	*cmds;
	char	**envp;
	pid_t	pid;
}		t_prompt;

typedef struct s_mini
{
	char	**full_cmd;
	char	*full_path;
	int	infile;
	int	outfile;
}		t_mini;

enum	ms_errors
{
	QUOTE_ERROR = 1,
	NO_DIR = 2,
	NO_PERM = 3,
	NO_CMD = 6,
	DUPERROR = 7,
	FORKERROR = 8,
	PIPERROR = 9,
	PIPENDERROR = 10,
	MEMORY = 11,
	IS_DIR = 12,
	ISNOT_DIR = 13
};

#endif