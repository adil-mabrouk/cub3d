/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 20:44:50 by amabrouk          #+#    #+#             */
/*   Updated: 2025/01/25 21:05:45 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	render_floor(t_game *game, int column, double wall_bottom)
{
	int	y;

	y = wall_bottom;
	while (y < HEIGHT)
	{
		mlx_put_pixel(game->img, column, y, game->pars->f_color);
		y++;
	}
}

void	render_ceiling(t_game *game, int column, double wall_height)
{
	double	screen_bottom;
	int		y;

	y = 0;
	screen_bottom = (HEIGHT / 2) - (wall_height / 2);
	while (y < screen_bottom)
	{
		mlx_put_pixel(game->img, column, y, game->pars->c_color);
		y++;
	}
}

static bool	ftt_check(t_game *game, int x, int y)
{
	if (y > 0 && x > 0 && y < game->pars->len_rows * TILE_SIZE
		&& x < game->pars->len_columns * TILE_SIZE)
		return (true);
	return (false);
}

void	render_minimap(t_game *game)
{
	t_cordinate	c;

	c.y = ((int)ceil(game->pars->player.y) - TILE_SIZE * 2.5) - 1;
	c.k = -1;
	while (++c.k < (TILE_SIZE * 5) && ++c.y >= INT_MIN)
	{
		c.x = ((int)ceil(game->pars->player.x) - TILE_SIZE * 2.5) - 1;
		c.j = -1;
		while (++c.j < (TILE_SIZE * 5) && ++c.x >= INT_MIN)
		{
			c.f = ftt_check(game, c.x, c.y);
			if (c.f
				&& (game->pars->map[c.y / TILE_SIZE][c.x / TILE_SIZE] == '1'))
				mlx_put_pixel(game->mini_map, c.j, c.k, get_rgb(0, 0, 255));
			else if (c.f
				&& game->pars->map[c.y / TILE_SIZE][c.x / TILE_SIZE] == 'D')
				mlx_put_pixel(game->mini_map, c.j, c.k, get_rgb(128, 0, 0));
			else if (c.f
				&& game->pars->map[c.y / TILE_SIZE][c.x / TILE_SIZE] == 'O')
				mlx_put_pixel(game->mini_map, c.j, c.k, get_rgb(255, 255, 255));
			else
				mlx_put_pixel(game->mini_map, c.j, c.k, get_rgb(0, 0, 0));
		}
	}
	return (draw_player(game, MINI_MAP_WIDTH / 2, MINI_MAP_HEIGHT / 2, 4));
}
