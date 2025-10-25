NAME = minishell

SOLONG = minishell.out

CC = cc

FLAGS = -Wall -Werror -Wextra -I Libft/includes -I .

LIBFT_PATH = ./Libft
LIBFT = $(LIBFT_PATH)/libft.a

SRC = src

FILES = $(SRC)/minishell.c\

OBJECTS = $(FILES:.c=.o)

$(NAME): $(OBJECTS) $(LIBFT)
	$(CC) $(FLAGS) $(OBJECTS) $(LIBFT) -o $(NAME)

$(OBJECTS):	src/%.o : src/%.c
	$(CC) $(FLAGS) -c $< -o $@

$(LIBFT):
	make -s -C $(LIBFT_PATH)

all: $(NAME)

clean:
	@ rm -rf $(OBJECTS) $(OBJECTS_BONUS)
	@ make clean -s -C $(LIBFT_PATH)

fclean: clean
	@ rm -rf $(NAME_BONUS) $(NAME) $(LIBFT) 
	@ make fclean -s -C ./Libft

re: fclean all

.PHONY: all re clean fclean
