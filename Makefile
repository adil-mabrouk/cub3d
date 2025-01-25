# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/22 10:25:25 by amabrouk          #+#    #+#              #
#    Updated: 2025/01/25 10:51:27 by isrkik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

BONUS_NAME = cub3D_bonus

CC = gcc

CFLAGS = -Werror -Wextra -Wall -I/Users/$(USER)/Desktop/MLX42/include/MLX42/  -fsanitize=address
DFLAGS = .MLX42/build/libmlx42.a -lglfw -L /Users/$(USER)/brew/opt/glfw/lib

SRC_MAN = mandatory/cub3d.c \
		mandatory/raycasting.c \
		mandatory/parsing/main/main.c \
		mandatory/parsing/utils/utils.c \
	  	mandatory/parsing/gnl.c \
		mandatory/parsing/utils/utils2.c \
		mandatory/parsing/utils/utils3.c \
		mandatory/parsing/main/map_pars.c \
		mandatory/parsing/main/pars_tex_colors.c\
		mandatory/textures.c \
		mandatory/parsing/utils/utils4.c \
		mandatory/parsing/main/pars_tex_colors2.c \
		mandatory/parsing/main/map_pars2.c \
		mandatory/parsing/main/map_pars3.c \
		mandatory/parsing/main/map_pars4.c \
	  

SRC_BONUS = bonus/cub3d_bonus.c \
			bonus/raycasting_bonus.c \
			bonus/parsing_bonus/gnl_bonus.c \
			bonus/textures_bonus.c \
			bonus/sprites.c\
			bonus/parsing_bonus/main_bonus/main_bonus.c \
 			bonus/parsing_bonus/utils_bonus/utils_bonus.c \
			bonus/parsing_bonus/utils_bonus/utils2_bonus.c \
			bonus/parsing_bonus/utils_bonus/utils3_bonus.c \
			bonus/parsing_bonus/utils_bonus/utils4_bonus.c \
			bonus/parsing_bonus/main_bonus/pars_tex_colors_bonus.c\
			bonus/parsing_bonus/main_bonus/pars_tex_colors2_bonus.c \
			bonus/parsing_bonus/main_bonus/map_pars_bonus.c \
			bonus/parsing_bonus/main_bonus/map_pars2_bonus.c \
			bonus/parsing_bonus/main_bonus/map_pars3_bonus.c \
			bonus/parsing_bonus/main_bonus/map_pars4_bonus.c \

OBJ_MAN = $(SRC_MAN:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: mlx $(NAME)

$(NAME): $(OBJ_MAN)
	$(CC) $(CFLAGS) -g $(OBJ_MAN) $(DFLAGS) -lm -o $(NAME)

mandatory/%.o: mandatory/%.c mandatory/cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_NAME) : $(OBJ_BONUS)
	$(CC) $(CFLAGS) -g $(OBJ_BONUS) $(DFLAGS) -lm -o $(BONUS_NAME)

bonus/%.o: bonus/%.c bonus/cub3d_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus : mlx $(BONUS_NAME)	

clean:
	rm -rf $(OBJ_MAN) $(OBJ_BONUS)
	@if [ -d .MLX42/build ]; then \
		cd .MLX42/build && make clean; \
	fi

fclean: clean
	rm -rf $(NAME) $(BONUS_NAME) .MLX42/build

re: fclean all

mlx:
	cd .MLX42 && cmake -B build && cmake --build build -j4

.PHONY: fclean all clean re bonus mlx
