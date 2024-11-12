NAME = ft_ls

SRC = main.c $(wildcard parsing/*.c) $(wildcard execution/*.c)
OBJS = $(SRC:.c=.o)

LIBFT = libft/libft.a

INCLUDES = -Iincludes -Ilibft

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C libft

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re