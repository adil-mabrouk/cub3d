# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/22 10:25:25 by amabrouk          #+#    #+#              #
#    Updated: 2025/01/23 16:18:37 by isrkik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

BONUS_NAME = cub3D_bonus

CC = gcc

CFLAGS = -Werror -Wextra -Wall -I/Users/$(USER)/Desktop/MLX42/include/MLX42/  -fsanitize=address

DFLAGS = mandatory/libmlx42.a -lglfw \
		 #-framework Cocoa -framework OpenGL -framework IOKit

SRC_MAN = mandatory/cub3d.c mandatory/raycasting.c mandatory/parsing/main/main.c mandatory/parsing/utils/utils.c \
	  mandatory/parsing/gnl.c mandatory/parsing/utils/utils2.c \
	  mandatory/parsing/utils/utils3.c mandatory/parsing/main/map_pars.c mandatory/parsing/main/pars_tex_colors.c\
	  mandatory/textures.c mandatory/parsing/utils/utils4.c mandatory/parsing/main/pars_tex_colors2.c \
	  mandatory/parsing/main/map_pars2.c mandatory/parsing/main/map_pars3.c mandatory/parsing/main/map_pars4.c \
	  

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

all: $(NAME)

$(NAME): $(OBJ_MAN)
	$(CC) $(CFLAGS) -g $(OBJ_MAN) $(DFLAGS) -lm -o $(NAME)

mandatory/%.o: mandatory/%.c mandatory/cub3d.h
	$(CC) -c $< -o $@ $(CFLAGS) -g

$(BONUS_NAME) : $(OBJ_BONUS)
	$(CC) $(CFLAGS) -g $(OBJ_BONUS) $(DFLAGS) -lm -o $(BONUS_NAME)

bonus/%.o: bonus/%.c bonus/cub3d_bonus.h
	$(CC) -c $< -o $@ $(CFLAGS) -g

bonus : $(BONUS_NAME)	

clean:
	rm -f $(OBJ_MAN) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: fclean all clean re bonus
