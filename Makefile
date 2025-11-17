NAME = minishell

CC = cc

FLAGS = -Wall -Werror -Wextra -I Libft/includes -I ./include

LIBFT_PATH = ./Libft
LIBFT = $(LIBFT_PATH)/libft.a

RL = -lreadline

SRC = src
SRC_PARSE = $(SRC)/parsing
SRC_EXEC = $(SRC)/execution

COMMON_SRC = $(SRC)/main.c\
			$(SRC)/envp.c\
			$(SRC)/prompt.c\
			$(SRC)/signals.c\
			$(SRC)/utils.c\
			$(SRC)/utils2.c\
			$(SRC)/cmd_perror.c

PARSE_SRC = $(SRC_PARSE)/expand.c\
			$(SRC_PARSE)/fill_node.c\
			$(SRC_PARSE)/ft_cmdsubsplit.c\
			$(SRC_PARSE)/ft_cmdtrim.c\
			$(SRC_PARSE)/ft_strtrim_all.c\
			$(SRC_PARSE)/get_params.c\
			$(SRC_PARSE)/heredoc.c\
			$(SRC_PARSE)/parse_args.c

EXEC_SRC = $(SRC_EXEC)/cmd_cd.c\
			$(SRC_EXEC)/cmd_exit.c\
			$(SRC_EXEC)/cmd_export_unset.c\
			$(SRC_EXEC)/cmd_others.c\
			$(SRC_EXEC)/cmd_pwd_echo_env.c\
			$(SRC_EXEC)/filter_cmds.c\
			$(SRC_EXEC)/fork_cmds.c\
			$(SRC_EXEC)/full_path_cmd.c

FILES = $(COMMON_SRC) $(PARSE_SRC) $(EXEC_SRC)

OBJ_DIR = obj
OBJECTS = $(FILES:$(SRC)/%.c=$(OBJ_DIR)/%.o)

$(NAME): $(OBJECTS) $(LIBFT)
	$(CC) $(FLAGS) $(OBJECTS) $(LIBFT) -o $(NAME) $(RL)

$(OBJ_DIR)/%.o: $(SRC)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c $< -o $@

$(LIBFT):
	make -s -C $(LIBFT_PATH)

all: $(NAME)

clean:
	@ rm -rf $(OBJ_DIR)
	@ make clean -s -C $(LIBFT_PATH)

fclean: clean
	@ rm -rf $(NAME) $(LIBFT) 
	@ make fclean -s -C ./Libft

re: fclean all

.PHONY: all re clean fclean
