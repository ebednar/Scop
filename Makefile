# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 14:23:06 by twitting          #+#    #+#              #
#    Updated: 2020/03/06 18:32:03 by ebednar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop
SRC = ./src/main.c
LIBFT = ./libft/libft.a
OBJECTS = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes -I libft -I GLFW/include 
FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit
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
