#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42.h"
# include <stdlib.h>
# include <math.h>
# include <stdio.h>

# define ROWS 15
# define COLUMS 20
# define TILE_SIZE 32
# define WIDTH 640
# define HEIGHT 480
# define FOV M_PI / 3

typedef struct s_player {
	double		x;
	double		y;
	int 	radius;
	double	angle;
}		t_player;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			map[15][20];
	t_player	player;
	int			rows;
	int			colums;
}	t_game;

typedef struct s_ray
{
	double	angle;
	int		is_facing_down;
	int		is_facing_up;
	int		is_facing_right;
	int		is_facing_left;
	double	hor_wall_hit_x;
	double	hor_wall_hit_y;
	double	horz;
	double	vert;
}				t_ray;

void	ft_raycast(t_game *game);
// void	draw_line(t_game *game, int x1, int y1, int color);

#endif