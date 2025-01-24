/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:16:02 by amabrouk          #+#    #+#             */
/*   Updated: 2025/01/24 10:35:46 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	collide_with_wall(t_game *game, double new_x, double new_y)
{
	double x = new_x - 2;
	double y;
	int	grid_x;
	int	grid_y;

	while (x <= new_x + 2)
	{
		y = new_y - 2;
		while (y <= new_y + 2)
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

void handle_keys(t_game *game)
{
    t_player *player = &game->pars->player;

    if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
    {
        mlx_terminate(game->mlx);
        exit(0);
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_W))
        collide_with_wall(game, player->x + SPEED * cos(player->angle), player->y + SPEED * sin(player->angle));
    else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
        collide_with_wall(game, player->x - SPEED * cos(player->angle), player->y - SPEED * sin(player->angle));
    else if (mlx_is_key_down(game->mlx, MLX_KEY_A))
        collide_with_wall(game, player->x - SPEED * cos(player->angle + M_PI_2), player->y - SPEED * sin(player->angle + M_PI_2));
    else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
        collide_with_wall(game, player->x + SPEED * cos(player->angle + M_PI_2), player->y + SPEED * sin(player->angle + M_PI_2));
    if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
        player->angle -= M_PI / 60.0;
    if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
        player->angle += M_PI / 60.0;
}

void	clear_img(mlx_image_t *img)
{
	int	y;
	int	x;

	y = -1;
	while (++y < (int)img->height)
	{
		x = -1;
		while (++x < (int)img->width)
			mlx_put_pixel(img, x, y, create_rgb(255, 255, 255));
	}
}

void loop_hook(void *param)
{
    t_game *game = (t_game *)param;

    handle_keys(game);
    clear_img(game->img);
	ft_raycast(game);
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
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->width = game->pars->len_columns * TILE_SIZE;
	game->height = game->pars->len_rows * TILE_SIZE;
	load_texture(&game->textures.north, game->pars->north);
    load_texture(&game->textures.south, game->pars->south);
    load_texture(&game->textures.east, game->pars->east);
    load_texture(&game->textures.west, game->pars->west);
}
