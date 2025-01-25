/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horz_inter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 20:16:50 by amabrouk          #+#    #+#             */
/*   Updated: 2025/01/25 20:25:03 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	get_horz_distance(t_game *game, t_ray *ray)
{
	double	next_x;
	double	next_y;
	double	x_tocheck;
	double	y_tocheck;

	next_x = ray->x_inter;
	next_y = ray->y_inter;
	while (next_x >= 0 && next_x <= game->width
		&& next_y >= 0 && next_y <= game->height)
	{
		x_tocheck = next_x;
		if (ray->is_facing_up)
			y_tocheck = next_y - 1;
		else
			y_tocheck = next_y;
		if (hit_wall(game, x_tocheck, y_tocheck))
		{
			ray->hor_wall_hit_x = next_x;
			ray->hor_wall_hit_y = next_y;
			break ;
		}
		next_x += ray->x_step;
		next_y += ray->y_step;
	}
	return (distance(game, next_x, next_y));
}

double	horz_inter(t_game *game, t_ray *ray)
{
	if (ray->angle > 0 && ray->angle < M_PI)
		ray->is_facing_down = true;
	else
		ray->is_facing_down = false;
	ray->is_facing_up = !ray->is_facing_down;
	if (ray->angle < M_PI_2 || ray->angle > 3 * M_PI_2)
		ray->is_facing_right = true;
	else
		ray->is_facing_right = false;
	ray->is_facing_left = !ray->is_facing_right;
	ray->y_inter = floor(game->pars->player.y / TILE_SIZE) * TILE_SIZE;
	if (ray->is_facing_down)
		ray->y_inter += TILE_SIZE;
	ray->x_inter = game->pars->player.x
		+ (ray->y_inter - game->pars->player.y) / tan(ray->angle);
	ray->y_step = TILE_SIZE;
	if (ray->is_facing_up)
		ray->y_step *= -1;
	ray->x_step = TILE_SIZE / tan(ray->angle);
	if (ray->is_facing_left && ray->x_step > 0)
		ray->x_step *= -1;
	if (ray->is_facing_right && ray->x_step < 0)
		ray->x_step *= -1;
	return (get_horz_distance(game, ray));
}
