/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:50:50 by amabrouk          #+#    #+#             */
/*   Updated: 2025/01/26 13:19:20 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	render_sprite(game);
}

void	load_texture(mlx_texture_t **texture, char *path)
{
	*texture = mlx_load_png(path);
	if (!*texture)
	{
		ft_putstr_fd("Error loading texture\n", 2);
		exit(1);
	}
}

void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_Y && keydata.action == MLX_PRESS)
		game->sprite.show_sprite = !game->sprite.show_sprite;
	if (keydata.key == MLX_KEY_LEFT_ALT && keydata.action == MLX_PRESS)
	{
		game->pars->lock = !game->pars->lock;
		if (game->pars->lock)
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
		else
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
	}
}

void	x_button(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_terminate(game->mlx);
	exit(0);
}
