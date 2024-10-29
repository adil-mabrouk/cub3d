NAME = cub3d

CC = cc

CFLAGS = -Werror -Wextra -Wall -I/Users/$(USER)/Desktop/MLX42/include -g -fsanitize=address

DFLAGS = /Users/$(USER)/Desktop/MLX42/libmlx42.a -lglfw \
		 -framework Cocoa -framework OpenGL -framework IOKit

SRC = parsing/main/main.c parsing/utils/utils.c \
	  parsing/gnl.c parsing/utils/utils2.c \
	  parsing/utils/utils3.c parsing/main/first_part.c \
	  

OBJ = $(SRC:.c=.o)

%.o : %.c cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ)  -L/Users/$(USER)/brew/opt/glfw/lib $(DFLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: fclean all clean re