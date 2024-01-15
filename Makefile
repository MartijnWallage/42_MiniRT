# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwallage <mwallage@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/15 15:03:37 by mwallage          #+#    #+#              #
#    Updated: 2024/01/15 15:03:42 by mwallage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -Ofast -g
SRCDIR		:= ./src
OBJDIR		:= ./obj
INCDIR		:= ./inc
LIBFTDIR	:= ./libft
LIBFT		:= $(LIBFTDIR)/libft.a
MLX42		:= ./MLX42/build/libmlx42.a
HEADERS		:= -I$(INCDIR) -I$(LIBFTDIR)
SRC			:= main.c \
				parser/parser.c \
				parser/parser_utils.c \
				parser/parser_double.c \
				parser/parser_vector.c
SRC			:= $(addprefix $(SRCDIR)/, $(SRC))
OBJ			:= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
MAKE		:= make
NAME		:= miniRT

all: $(NAME)

$(NAME): $(LIBFT) $(OBJDIR) $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -L$(LIBFTDIR) -lft -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(OBJDIR):
	mkdir obj;
	mkdir obj/parser;

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< $(HEADERS) -o $@

clean:
	$(MAKE) clean -C $(LIBFTDIR)
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C $(LIBFTDIR)
	rm -rf $(OBJDIR)
	rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re
