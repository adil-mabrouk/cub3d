# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/22 10:25:25 by amabrouk          #+#    #+#              #
#    Updated: 2024/10/26 18:56:13 by amabrouk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = cc

CFLAGS = -Werror -Wextra -Wall -g -Iinclude # -Ofast -fsanitize=address
DFLAGS = libmlx42.a -lglfw -L /Users/amabrouk/.brew/opt/glfw/lib # -framework Cocoa -framework OpenGL -framework IOKit

SRC = cub3d.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) cub3d.h
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(DFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all