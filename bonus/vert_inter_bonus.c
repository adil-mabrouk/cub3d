/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vert_inter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 20:38:55 by amabrouk          #+#    #+#             */
/*   Updated: 2025/01/25 20:45:29 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	distance(t_game *game, double x, double y)
{
	return (sqrt(pow(x - game->pars->player.x, 2)
			+ pow(y - game->pars->player.y, 2)));
}

double	norm_angle(t_ray *ray)
{
	ray->angle = fmod(ray->angle, 2 * M_PI);
	if (ray->angle < 0)
		ray->angle += 2 * M_PI;
	return (ray->angle);
}

static double	get_vet_distance(t_game *game, t_ray *ray)
{
	double	x_tocheck;
	double	y_tocheck;
	double	next_x;
	double	next_y;

	next_x = ray->x_inter;
	next_y = ray->y_inter;
	while (next_x >= 0 && next_x <= game->width && next_y >= 0
		&& next_y <= game->height)
	{
		if (ray->is_facing_left)
			x_tocheck = next_x - 1;
		else
			x_tocheck = next_x;
		y_tocheck = next_y;
		if (hit_wall(game, x_tocheck, y_tocheck))
		{
			ray->vert_wall_hit_x = next_x;
			ray->vert_wall_hit_y = next_y;
			break ;
		}
		next_x += ray->x_step;
		next_y += ray->y_step;
	}
	return (distance(game, next_x, next_y));
}

double	ver_inter(t_game *game, t_ray *ray)
{
	ray->x_inter = floor(game->pars->player.x / TILE_SIZE) * TILE_SIZE;
	if (ray->is_facing_right)
		ray->x_inter += TILE_SIZE;
	ray->y_inter = game->pars->player.y
		+ (ray->x_inter - game->pars->player.x) * tan(ray->angle);
	if (ray->is_facing_left)
		ray->x_step = TILE_SIZE * (-1);
	else
		ray->x_step = TILE_SIZE;
	ray->y_step = TILE_SIZE * tan(ray->angle);
	if (ray->is_facing_up && ray->y_step > 0)
		ray->y_step *= -1;
	if (ray->is_facing_down && ray->y_step < 0)
		ray->y_step *= -1;
	return (get_vet_distance(game, ray));
}
