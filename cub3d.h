#ifndef CUB3D_H
# define CUB3D_H

#include "MLX42.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

typedef struct s_player {
	double		x;
	double		y;
	int 	radius;
	float	angle;
}		t_player;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			map[15][20];
	t_player	player;
	int			tile_size;
	int			width;
	int			height;
	int			rows;
	int			colums;
}	t_game;


#endif