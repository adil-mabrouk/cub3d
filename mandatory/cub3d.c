/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:16:02 by amabrouk          #+#    #+#             */
/*   Updated: 2025/01/25 13:52:57 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	hit_wall(t_game *game, double x, double y)
{
	int tile_x = floor(x / TILE_SIZE);
	int tile_y = floor(y / TILE_SIZE);
	if (x < 0 || x >= game->width || y < 0 || y >= game->height)
		return 1;
	else if (tile_y < 0 || tile_y >= game->pars->len_rows || tile_x < 0 || tile_x >= game->pars->len_columns)
		return 1;
	else if (game->pars->map[tile_y][tile_x] == '1' || game->pars->map[tile_y][tile_x] == 'D')
        return 1;
	return 0;
}

int	collide_with_wall(t_game *game, double new_x, double new_y)
{
    if (hit_wall(game, new_x, game->pars->player.y)) //horizental
        new_x = game->pars->player.x;// kan usi lblasa nit d 'y' bach ntchecki biha ghir 'x' rasha
    if (hit_wall(game, game->pars->player.x, new_y))//vertical
        new_y = game->pars->player.y;// kan usi lblasa nit d 'x' bach ntchecki biha ghir 'y' rasha
    if (hit_wall(game, new_x, new_y))
        return 1;
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
		ft_free_all(game->pars->map);
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
        player->angle -= M_PI / 50.0;
    if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
        player->angle += M_PI / 50.0;
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

void load_texture(mlx_texture_t **texture, char *path, t_game *game)
{
    *texture = mlx_load_png(path);
	if (!*texture)
	{
		ft_putstr_fd("Error loading texture\n", 2);
		ft_free_all(game->pars->map);
		exit(1);
	}
}

void    x_button(void *param)
{
    t_game  *game;

    game = (t_game *)param;
    mlx_terminate(game->mlx);
	ft_free_all(game->pars->map);
    exit(0);
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "Map", true);
	mlx_close_hook(game->mlx, &x_button, game);
	if (!game->mlx)
	{
		ft_putstr_fd("Error init mlx\n", 2);
		ft_free_all(game->pars->map);
		exit(1);
	}
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->width = game->pars->len_columns * TILE_SIZE;
	game->height = game->pars->len_rows * TILE_SIZE;
	load_texture(&game->textures.north, game->pars->north, game);
    load_texture(&game->textures.south, game->pars->south, game);
    load_texture(&game->textures.east, game->pars->east, game);
    load_texture(&game->textures.west, game->pars->west, game);
}
