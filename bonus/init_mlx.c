/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:58:21 by amabrouk          #+#    #+#             */
/*   Updated: 2025/01/26 18:48:40 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_game(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "Map", true);
	mlx_close_hook(game->mlx, &x_button, game);
	if (!game->mlx)
	{
		ft_putstr_fd("Error init mlx\n", 2);
		exit(1);
	}
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->mini_map = mlx_new_image(game->mlx, MINI_MAP_WIDTH, MINI_MAP_HEIGHT);
	game->width = game->pars->len_columns * TILE_SIZE;
	game->height = game->pars->len_rows * TILE_SIZE;
	load_texture(&game->textures.north, game->pars->north);
	load_texture(&game->textures.south, game->pars->south);
	load_texture(&game->textures.east, game->pars->east);
	load_texture(&game->textures.west, game->pars->west);
	load_texture(&game->textures.door, "/home/amabrouk/cub3d/bonus/\
parsing_bonus/textures_bonus/door.png");
	init_sprite(game);
}
