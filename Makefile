# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 14:23:06 by twitting          #+#    #+#              #
#    Updated: 2020/11/05 19:57:13 by ebednar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop
SRC = 	./src/main.c \
		./src/shaders.c \
		./src/shader_light_u.c \
		./src/events.c \
		./src/movement.c \
		./src/render.c \
		./src/textures.c \
		./src/init.c \
		./src/matrices.c \
		./src/matrix_proj.c \
		./src/matrix_rotate.c \
		./src/camera.c \
		./src/model.c \
		./src/read_indicies.c \
		./src/fill_verticies.c \
		./src/draw.c \
		./src/material.c \
		./src/mouse.c \
		./src/error.c
LIBFT = ./libft/libft.a
OBJECTS = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes -I libft -I GLFW/include
FRAMEWORKS = -framework OpenGL -framework Cocoa -framework IOKit
LIBGLFW = ./GLFW/lib-macos/libglfw3.a
all: $(NAME)

$(NAME): $(OBJECTS)
	make -C libft/
	gcc $(FLAGS) $(INCLUDES) $(OBJECTS) $(LIBFT) $(LIBGLFW) $(FRAMEWORKS) -o $(NAME)

%.o: %.c
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	make clean -C libft/
	/bin/rm -f $(OBJECTS)

fclean: clean
	make fclean -C libft/
	/bin/rm -f $(NAME)

re: fclean all
