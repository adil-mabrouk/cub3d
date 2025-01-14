# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: i61mail <i61mail@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/22 10:25:25 by amabrouk          #+#    #+#              #
#    Updated: 2025/01/13 11:45:38 by i61mail          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = gcc

CFLAGS = -Werror -Wextra -Wall -I/Users/$(USER)/Desktop/MLX42/include/MLX42/  -fsanitize=address

DFLAGS = ./libmlx42.a -lglfw \
		 #-framework Cocoa -framework OpenGL -framework IOKit

SRC = cub3d.c raycasting.c parsing/main/main.c parsing/utils/utils.c \
	  parsing/gnl.c parsing/utils/utils2.c \
	  parsing/utils/utils3.c parsing/main/map_pars.c parsing/main/colors_textures_pars.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -g $(OBJ) $(DFLAGS) -lm -o $(NAME)

%.o: %.c cub3d.h
	$(CC) -c $< -o $@ $(CFLAGS) -g

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: fclean all clean re
