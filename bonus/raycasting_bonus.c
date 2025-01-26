/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:17:19 by amabrouk          #+#    #+#             */
/*   Updated: 2025/01/26 12:12:27 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	get_color(t_game *game, int x, int y)
{
	if (y > 0 && x > 0)
	{
		x /= TILE_SIZE;
		y /= TILE_SIZE;
		if (game->pars->map[y][x] == '1')
			return (get_rgb(128, 128, 128));
		else if (game->pars->map[y][x] == 'D')
			return (get_rgb(0, 0, 255));
		else if (game->pars->map[y][x] == '0')
			return (get_rgb(255, 255, 255));
	}
	return (get_rgb(128, 128, 128));
}

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

void	cast_ray(t_game *game, t_ray *ray, int column)
{
	double	distance;
	double	wall_height;
	double	wall_bottom;

	ray->horz = horz_inter(game, ray);
	ray->vert = ver_inter(game, ray);
	if (ray->horz < ray->vert)
		distance = ray->horz;
	else
		distance = ray->vert;
	distance *= cos(ray->angle - game->pars->player.angle);
	wall_height = (TILE_SIZE * (WIDTH / 2) / tan((FOV / 3) / 2)) / distance;
	wall_bottom = (HEIGHT / 2) + (wall_height / 2);
	render_textured_wall(game, ray, column, wall_height);
	render_floor(game, column, wall_bottom);
	render_ceiling(game, column, wall_height);
}

void	ft_raycast(t_game *game)
{
	int		i;
	t_ray	ray;

	ray.angle = game->pars->player.angle - (FOV / 3) / 2;
	i = 0;
	while (i < WIDTH)
	{
		ray.angle = norm_angle(&ray);
		cast_ray(game, &ray, i);
		ray.angle += (FOV / 3) / WIDTH;
		i++;
	}
	render_minimap(game);
}
