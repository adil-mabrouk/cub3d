/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:16:02 by amabrouk          #+#    #+#             */
/*   Updated: 2025/01/26 15:53:55 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_img(mlx_image_t *img)
{
	int	y;
	int	x;

	y = -1;
	while (++y < (int)img->height)
	{
		x = -1;
		while (++x < (int)img->width)
			mlx_put_pixel(img, x, y, get_rgb(255, 255, 255));
	}
}

void	loop_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_keys(game);
	clear_img(game->img);
	ft_raycast(game);
}

void	load_texture(mlx_texture_t **texture, char *path, t_game *game)
{
	*texture = mlx_load_png(path);
	if (!*texture)
	{
		ft_putstr_fd("Error loading texture\n", 2);
		ft_free_all(game->pars->map);
		exit(1);
	}
}

void	x_button(void *param)
{
	t_game	*game;

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
