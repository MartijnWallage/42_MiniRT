CC=cc
CFLAGS= -Wall -Wextra -Werror -Ofast -g
LIBFT_PATH=include/libft
LIBFT=libft.a

NAME=miniRT
SRC=main.c parsing/parsing.c parsing/parsing_utils.c
MAKE=make
OBJ=$(SRC:.c=.o)

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFT_PATH)
	cp $(LIBFT_PATH)/$(LIBFT) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(SRC) -L . -lft

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< -I $(LIBFT)

all: $(NAME)

clean:
	$(MAKE) clean -C $(LIBFT_PATH)
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_PATH)
	rm -f $(NAME)
	rm -f $(LIBFT)
	
re: fclean all

.PHONY: all clean fclean re