/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:16:02 by amabrouk          #+#    #+#             */
/*   Updated: 2025/01/26 13:19:28 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_player(t_game *game, int px, int py, int ray)
{
	int	i;
	int	j;
	int	dx;
	int	dy;

	i = px - ray - 1;
	while (++i <= px + ray)
	{
		j = py - ray - 1;
		while (++j <= py + ray)
		{
			dx = i - px;
			dy = j - py;
			if (dx * dx + dy * dy <= ray * ray)
			{
				mlx_put_pixel(game->mini_map, i, j, get_rgb(255, 0, 0));
			}
		}
	}
}

int	collide_with_wall(t_game *game, double new_x, double new_y)
{
	if (hit_wall(game, new_x, game->pars->player.y))
		new_x = game->pars->player.x;
	if (hit_wall(game, game->pars->player.x, new_y))
		new_y = game->pars->player.y;
	if (hit_wall(game, new_x, new_y))
		return (1);
	game->pars->player.x = new_x;
	game->pars->player.y = new_y;
	return (0);
}

void	handle_door(t_game *game)
{
	double	check_x;
	double	check_y;
	int		tile_x;
	int		tile_y;

	check_x = game->pars->player.x + cos(game->pars->player.angle) * TILE_SIZE;
	check_y = game->pars->player.y + sin(game->pars->player.angle) * TILE_SIZE;
	tile_x = floor(check_x / TILE_SIZE);
	tile_y = floor(check_y / TILE_SIZE);
	if (tile_y >= 0 && tile_y < game->pars->len_rows
		&& tile_x >= 0 && tile_x < game->pars->len_columns)
	{
		if (mlx_is_key_down(game->mlx, MLX_KEY_O)
			&& game->pars->map[tile_y][tile_x] == 'D')
		{
			game->pars->map[tile_y][tile_x] = DOOR_OPEN;
		}
		else if (mlx_is_key_down(game->mlx, MLX_KEY_C)
			&& game->pars->map[tile_y][tile_x] == DOOR_OPEN)
		{
			game->pars->map[tile_y][tile_x] = 'D';
		}
	}
}

void	handle_keys(t_game *game)
{
	t_player	*player;

	player = &game->pars->player;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		mlx_terminate(game->mlx);
		exit(0);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		collide_with_wall(game, player->x + SPEED * cos(player->angle),
			player->y + SPEED * sin(player->angle));
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		collide_with_wall(game, player->x - SPEED * cos(player->angle),
			player->y - SPEED * sin(player->angle));
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		collide_with_wall(game, player->x - SPEED * cos(player->angle + M_PI_2),
			player->y - SPEED * sin(player->angle + M_PI_2));
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		collide_with_wall(game, player->x + SPEED * cos(player->angle + M_PI_2),
			player->y + SPEED * sin(player->angle + M_PI_2));
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		player->angle -= M_PI / 60.0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		player->angle += M_PI / 60.0;
	handle_door(game);
}

void	mouse_hook(double curr_x_pos, double curr_y_pos, void *param)
{
	static double	last_x_pos;
	double			delta_x;
	t_game			*game;

	(void)curr_y_pos;
	game = (t_game *)param;
	if (game->pars->lock == true)
	{
		delta_x = curr_x_pos - last_x_pos;
		game->pars->player.angle += delta_x * 0.001;
		last_x_pos = curr_x_pos;
	}
}
