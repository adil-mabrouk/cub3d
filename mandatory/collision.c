/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 20:22:13 by amabrouk          #+#    #+#             */
/*   Updated: 2025/01/25 20:37:28 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hit_wall(t_game *game, double x, double y)
{
	int	tile_x;
	int	tile_y;

	tile_x = floor(x / TILE_SIZE);
	tile_y = floor(y / TILE_SIZE);
	if (x < 0 || x >= game->width || y < 0 || y >= game->height)
		return (1);
	else if (tile_y < 0 || tile_y >= game->pars->len_rows
		|| tile_x < 0 || tile_x >= game->pars->len_columns)
		return (1);
	else if (game->pars->map[tile_y][tile_x] == '1'
				|| game->pars->map[tile_y][tile_x] == 'D')
		return (1);
	return (0);
}

static int	collide_with_wall(t_game *game, double new_x, double new_y)
{
	if (hit_wall(game, new_x, game->pars->player.y)) //horizental
		new_x = game->pars->player.x; // kan usi lblasa nit d 'y' bach ntchecki biha ghir 'x' rasha
	if (hit_wall(game, game->pars->player.x, new_y)) //vertical
		new_y = game->pars->player.y; // kan usi lblasa nit d 'x' bach ntchecki biha ghir 'y' rasha
	if (hit_wall(game, new_x, new_y))
		return (1);
	game->pars->player.x = new_x;
	game->pars->player.y = new_y;
	return (0);
}

void	handle_keys(t_game *game)
{
	t_player	*player;

	player = &game->pars->player;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		mlx_terminate(game->mlx);
		ft_free_all(game->pars->map);
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
		player->angle -= M_PI / 50.0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		player->angle += M_PI / 50.0;
}
