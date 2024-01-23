# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/15 15:03:37 by mwallage          #+#    #+#              #
#    Updated: 2024/01/22 16:08:07 by mwallage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -Wunreachable-code -Ofast -g
SRCDIR		:= ./src
OBJDIR		:= ./obj
INCDIR		:= ./inc
LIBFTDIR	:= ./libft
LIBFT		:= $(LIBFTDIR)/libft.a
MLXDIR		:= ./MLX42
MLX			:= $(MLXDIR)/build/libmlx42.a
HEADERS		:= -I$(INCDIR) -I$(LIBFTDIR)/inc -I$(MLXDIR)/include/MLX42
LIBS		:= -L$(LIBFTDIR) -lft $(MLX)
UNAME_S		:= $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LIBS	:= $(LIBS) -ldl -lglfw -pthread -lm
endif
ifeq ($(UNAME_S),Darwin)
	LIBS	:= $(LIBS) -Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.9/lib/" -pthread -lm
endif
SRC			:= main.c \
				test.c \
				parser/parser.c \
				parser/parser_checks.c \
				parser/parser_objects.c \
				parser/parser_utils.c \
				parser/parser_double.c \
				parser/parser_vector.c \
				clean/clean.c \
				graphics/hooks.c \
				graphics/put_pixel.c \
				graphics/colors.c \
				graphics/rotations.c \
				raytracer/raytracer.c \
				raytracer/vector_utils.c \
				raytracer/intersections.c \
				raytracer/math_utils.c
SRC			:= $(addprefix $(SRCDIR)/, $(SRC))
OBJ			:= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
MAKE		:= make
NAME		:= miniRT

all: $(NAME)


$(LIBFT): $(LIBFTDIR)
	$(MAKE) -C $(LIBFTDIR)

$(LIBFTDIR):
	git clone https://github.com/MartijnWallage/42_libft.git $@

$(MLX): $(MLXDIR)
	cmake $(MLXDIR) -B $(MLXDIR)/build;
	make -C$(MLXDIR)/build -j4;

$(MLXDIR):
	git clone https://github.com/codam-coding-college/MLX42.git $@

$(OBJDIR):
	mkdir $(OBJDIR);
	mkdir $(OBJDIR)/parser;
	mkdir $(OBJDIR)/raytracer;
	mkdir $(OBJDIR)/graphics;
	mkdir $(OBJDIR)/clean;

$(NAME): $(LIBFT) $(MLX) $(OBJDIR) $(OBJ)
	$(CC) $(OBJ) $(LIBS) $(HEADERS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/miniRT.h
	$(CC) $(CFLAGS) -c $< $(HEADERS) -o $@

clean:
	$(MAKE) clean -C $(LIBFTDIR)
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C $(LIBFTDIR)
	rm -rf $(LIBFTDIR)
	rm -rf $(MLXDIR)
	rm -rf $(OBJDIR)
	rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re
