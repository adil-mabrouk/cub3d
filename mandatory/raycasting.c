/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:17:19 by amabrouk          #+#    #+#             */
/*   Updated: 2025/01/25 20:35:42 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	wall_height = (TILE_SIZE * (WIDTH / 2) / tan(FOV / 2)) / distance;
	wall_bottom = (HEIGHT / 2) + (wall_height / 2);
	render_textured_wall(game, ray, column, wall_height);
	render_floor(game, column, wall_bottom);
	render_ceiling(game, column, wall_height);
}

void	ft_raycast(t_game *game)
{
	t_ray	ray;
	int		i;

	ray.angle = game->pars->player.angle - FOV / 2;
	i = 0;
	while (i < WIDTH)
	{
		ray.angle = norm_angle(&ray);
		cast_ray(game, &ray, i);
		ray.angle += FOV / WIDTH;
		i++;
	}
}
