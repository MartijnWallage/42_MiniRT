# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/15 15:03:37 by mwallage          #+#    #+#              #
#    Updated: 2024/02/20 16:53:05 by mwallage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKE		:= make
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -Wunreachable-code -Ofast -pthread
SRCDIR		:= ./src
OBJDIR		:= ./obj
INCDIR		:= ./inc
LIBFTDIR	:= ./libft
LIBFT		:= $(LIBFTDIR)/libft.a
MLXDIR		:= ./MLX42
MLX			:= $(MLXDIR)/build/libmlx42.a
HEADERS		:= -I$(INCDIR) -I$(LIBFTDIR)/inc -I$(MLXDIR)/include/MLX42
BONUS		:= 0
LIBS		:= -L$(LIBFTDIR) -lft $(MLX)
UNAME_S		:= $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LIBS	:= $(LIBS) -ldl -lglfw -lm
endif
ifeq ($(UNAME_S),Darwin)
	LIBS	:= $(LIBS) -Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.9/lib/" -lm
endif
SRC			:= main.c \
				clean/clean.c \
				clean/exit.c \
				graphics/hooks.c \
				graphics/put_pixel.c \
				graphics/colors.c \
				graphics/rotations.c \
				graphics/translate.c \
				math/math_utils.c \
				math/vector_utils_norm.c \
				math/vector_utils.c \
				parser/parser_camera.c \
				parser/parser_checks.c \
				parser/parser_cyl.c \
				parser/parser_disk.c \
				parser/parser_lights.c \
				parser/parser_objects.c \
				parser/parser_real.c \
				parser/parser_utils.c \
				parser/parser_vector.c \
				parser/parser.c \
				raytracer/raytracer.c \
				raytracer/compute_rays.c \
				raytracer/intersections.c \
				raytracer/cyl.c \
				raytracer/cyl_utils.c \
				raytracer/compute_color.c \
				raytracer/compute_color_utils.c
SRC			:= $(addprefix $(SRCDIR)/, $(SRC))
OBJ			:= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
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
	mkdir $(OBJDIR)/math;

$(NAME): $(LIBFT) $(MLX) $(OBJDIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) $(HEADERS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/miniRT.h
	$(CC) -DBONUS=$(BONUS) $(CFLAGS) -c $< $(HEADERS) -o $@

bonus:
	$(MAKE) BONUS:=1

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
