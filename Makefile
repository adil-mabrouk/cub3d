NAME = cub3d

CC = cc

CFLAGS = -Werror -Wextra -Wall -I/Users/isrkik/Desktop/MLX42/include -g -fsanitize=address

DFLAGS = -framework Cocoa -framework OpenGL -framework IOKit

SRC = parsing/main.c parsing/utils.c parsing/gnl.c

OBJ = $(SRC:.c=.o)

%.o : %.c cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ)  -L/Users/isrkik/brew/opt/glfw/lib /Users/isrkik/Desktop/MLX42/libmlx42.a -lglfw  $(DFLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: fclean all clean re