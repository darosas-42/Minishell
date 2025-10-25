NAME = libft.a

CC = cc

LIB = ar rcs

FLAGS = -Werror -Wall -Wextra -I ./includes

LIBFT_PATH = libft

PRINTF_PATH = Printf
PRINTF = $(PRINTF_PATH)/libftprintf.a

GNL_PATH = Get_next_line

LIBFT_FILES = $(LIBFT_PATH)/ft_isalpha.c\
	$(LIBFT_PATH)/ft_isdigit.c\
	$(LIBFT_PATH)/ft_isalnum.c\
	$(LIBFT_PATH)/ft_isascii.c\
	$(LIBFT_PATH)/ft_isprint.c\
	$(LIBFT_PATH)/ft_strlen.c\
	$(LIBFT_PATH)/ft_memset.c\
	$(LIBFT_PATH)/ft_bzero.c\
	$(LIBFT_PATH)/ft_memcpy.c\
	$(LIBFT_PATH)/ft_memmove.c\
	$(LIBFT_PATH)/ft_strlcpy.c\
	$(LIBFT_PATH)/ft_strlcat.c\
	$(LIBFT_PATH)/ft_toupper.c\
	$(LIBFT_PATH)/ft_tolower.c\
	$(LIBFT_PATH)/ft_strchr.c\
	$(LIBFT_PATH)/ft_strrchr.c\
	$(LIBFT_PATH)/ft_strncmp.c\
	$(LIBFT_PATH)/ft_memchr.c\
	$(LIBFT_PATH)/ft_memcmp.c\
	$(LIBFT_PATH)/ft_strnstr.c\
	$(LIBFT_PATH)/ft_atoi.c\
	$(LIBFT_PATH)/ft_calloc.c\
	$(LIBFT_PATH)/ft_strdup.c\
	$(LIBFT_PATH)/ft_substr.c\
	$(LIBFT_PATH)/ft_strjoin.c\
	$(LIBFT_PATH)/ft_strtrim.c\
	$(LIBFT_PATH)/ft_split.c\
	$(LIBFT_PATH)/ft_itoa.c\
	$(LIBFT_PATH)/ft_strmapi.c\
	$(LIBFT_PATH)/ft_striteri.c\
	$(LIBFT_PATH)/ft_putchar_fd.c\
	$(LIBFT_PATH)/ft_putstr_fd.c\
	$(LIBFT_PATH)/ft_putendl_fd.c\
	$(LIBFT_PATH)/ft_putnbr_fd.c\

LIBFT_BONUS = $(LIBFT_PATH)/ft_lstnew_bonus.c\
	$(LIBFT_PATH)/ft_lstadd_front_bonus.c\
	$(LIBFT_PATH)/ft_lstsize_bonus.c\
	$(LIBFT_PATH)/ft_lstlast_bonus.c\
	$(LIBFT_PATH)/ft_lstadd_back_bonus.c\
	$(LIBFT_PATH)/ft_lstdelone_bonus.c\
	$(LIBFT_PATH)/ft_lstclear_bonus.c\
	$(LIBFT_PATH)/ft_lstiter_bonus.c\
	$(LIBFT_PATH)/ft_lstmap_bonus.c\

GNL_FILES = $(GNL_PATH)/get_next_line_bonus.c\
	$(GNL_PATH)/get_next_line_utils_bonus.c\

PRINTF_FILES = $(PRINTF_PATH)/ft_printf.c\
	$(PRINTF_PATH)/ft_putchar.c\
	$(PRINTF_PATH)/ft_putnbr.c\
	$(PRINTF_PATH)/ft_putstr.c\
	$(PRINTF_PATH)/ft_unsnb.c\
	$(PRINTF_PATH)/ft_address.c\
	$(PRINTF_PATH)/ft_hexadec.c\

LIBFT_OBJS = $(LIBFT_FILES:%.c=%.o)
LIBFT_OBJS_BONUS = $(LIBFT_BONUS:%.c=%.o)
GNL_OBJS = $(GNL_FILES:%.c=%.o)
PRINTF_OBJS = $(PRINTF_FILES:%.c=%.o)

all: printf $(NAME)

$(NAME): $(LIBFT_OBJS) $(LIBFT_OBJS_BONUS) $(GNL_OBJS) $(PRINTF_OBJS)
	$(LIB) $(NAME) $(LIBFT_OBJS) $(LIBFT_OBJS_BONUS) $(GNL_OBJS) $(PRINTF_OBJS)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(LIBFT_OBJS) $(LIBFT_OBJS_BONUS) $(GNL_OBJS) $(PRINTF_OBJS)
	@echo "libft clean done!"

fclean: clean
	@rm -f $(NAME)
	@echo "libft fclean done!"

re: fclean all

.PHONY: re all clean fclean printf
