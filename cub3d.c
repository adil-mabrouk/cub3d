/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:16:02 by amabrouk          #+#    #+#             */
/*   Updated: 2025/01/18 11:52:10 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map(t_game *game)
{
	int r = -1;
	int	col;

	while (++r < game->pars->len_rows)
	{
		col = -1;
		while (++col < game->pars->len_columns)
		{
			int tile = game->pars->map[r][col];
			int x = col * TILE_SIZE;
			int y = r * TILE_SIZE;
			int color = tile == '1' ? 0x000000FF : 0x0000FF00;
			int i = -1;
			while (++i < TILE_SIZE)
			{
				int j = -1;
				while (++j < TILE_SIZE)
					mlx_put_pixel(game->img, x + i, y + j, color);
			}
		}
	}
}

// void	draw_line(t_game *game, int x1, int y1, int color)
// {
// 	double	dx = x1 - game->pars->player.x;
// 	double	dy = y1 - game->pars->player.y;
// 	int	steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy); // Determine the number of steps

// 	double	x_inc = dx / steps; // Calculate the increment in x for each step
// 	double	y_inc = dy / steps; // Calculate the increment in y for each step

// 	double	x = game->pars->player.x;
// 	double	y = game->pars->player.y;

// 	for (int i = 0; i <= steps; i++)
// 	{
// 		mlx_put_pixel(game->img, x, y, color); // Plot the pixel
// 		x += x_inc; // Increment x-coordinate by x_inc
// 		y += y_inc; // Increment y-coordinate by y_inc
// 	}
// }

void	draw_player(t_game *game)
{
	int i = -game->pars->player.radius;
	while (++i < game->pars->player.radius)
	{
		int	j = -game->pars->player.radius;
		while (++j < game->pars->player.radius)
			if (i * i + j * j <= game->pars->player.radius * game->pars->player.radius)
				mlx_put_pixel(game->img, game->pars->player.x + i, game->pars->player.y + j, 0xFF0000FF);
	}
	// int	line_x = game->pars->player.x + 50 * cos(game->player.angle);
	// int	line_y = game->pars->player.y + 50 * sin(game->player.angle);
	// draw_line(game, line_x, line_y, 0xFFFF00FF);
	// int r = 0;
	// while (r < game->pars->len_rows)
	// {
	// 	int c = 0;
	// 	while (c < game->pars->len_columns)
	// 	{
	// 		printf("%d  ", game->pars->map[r][c]);
	// 		c++;
	// 	}
	// 	printf("\n");
	// 	r++;
	// }
	// printf("done map\n");
	// printf("p.x == %f,   p.y == %f\n", game->pars->player.x, game->pars->player.y);
	ft_raycast(game);
}

int	collide_with_wall(t_game *game, double new_x, double new_y)
{
	double x = new_x;
	double y;
	int	grid_x;
	int	grid_y;

	while (x <= new_x)
	{
		y = new_y;
		while (y <= new_y)
		{
			grid_x = x / TILE_SIZE;
			grid_y = y / TILE_SIZE;
			if (game->pars->map[grid_y][grid_x] == '1')
				return 1;
			y++;
		}
		x++;
	}
	game->pars->player.x = new_x;
	game->pars->player.y = new_y;
	return 0;
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game		*game;
	t_player	*player;

	game = (t_game *)param;
	player = &game->pars->player;
	if (keydata.key == MLX_KEY_ESCAPE)
    {
        mlx_terminate(game->mlx);
        exit(0);
    }
	if (keydata.key == MLX_KEY_W && !collide_with_wall(game, player->x + 3 * cos(player->angle), player->y + 3 * sin(player->angle)))
	{
		player->x += 2 * cos(player->angle);
		player->y += 2 * sin(player->angle);
	}
	else if (keydata.key == MLX_KEY_S && !collide_with_wall(game, player->x - 3 * cos(player->angle), player->y - 3 * sin(player->angle)))
	{
		player->x -= 2 * cos(player->angle);
		player->y -= 2 * sin(player->angle);
	}
	else if (keydata.key == MLX_KEY_A && !collide_with_wall(game, player->x - 3 * cos(player->angle + M_PI_2), player->y - 3 * sin(player->angle + M_PI_2)))
	{
		player->x -= 2 * cos(player->angle + M_PI_2);
		player->y -= 2 * sin(player->angle + M_PI_2);
	}
	else if (keydata.key == MLX_KEY_D && !collide_with_wall(game, player->x + 3 * cos(player->angle + M_PI_2), player->y + 3 * sin(player->angle + M_PI_2)))
	{
		player->x += 2 * cos(player->angle + M_PI_2);
		player->y += 2 * sin(player->angle + M_PI_2);
	}
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == 1)
		player->angle -= M_PI / 12;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == 1)
		player->angle += M_PI / 12;
	else
		return ;
	mlx_delete_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	draw_map(game);
	draw_player(game);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}

void load_texture(mlx_texture_t **texture, char *path)
{
    *texture = mlx_load_png(path);
	if (!*texture)
	{
		printf("error loading texture\n");
		exit(1);
	}
}

void    x_button(void *param)
{
    t_game  *game;

    game = (t_game *)param;
    mlx_terminate(game->mlx);
    exit(0);
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "Map", true);
	mlx_close_hook(game->mlx, &x_button, game);
	if (!game->mlx)
	{
		printf("error initializing mlx\n");
		exit(1);
	}
	load_texture(&game->textures.north, game->pars->north);
    load_texture(&game->textures.south, game->pars->south);
    load_texture(&game->textures.east, game->pars->east);
    load_texture(&game->textures.west, game->pars->west);
	game->pars->player.radius = 10;
}
