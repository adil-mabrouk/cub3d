/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 01:31:51 by amabrouk          #+#    #+#             */
/*   Updated: 2024/11/20 19:12:37 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hit_wall(t_game *game, double x, double y)
{
	int tile_x = floor(x / TILE_SIZE);
	int tile_y = floor(y / TILE_SIZE);
	if (game->map[tile_y][tile_x] != 0)
		return 1;
	return 0;
}

double	get_vert_dis(t_game *game, t_ray *ray)
{
	double	x_inter;
	double	y_inter;
	double	x_step;
	double	y_step;
	// int hor_wall_content = 0;
	// bool found_hor_wall_hit = false;

	ray->is_facing_down = ray->angle > 0 && ray->angle < M_PI;
	ray->is_facing_up = !ray->is_facing_down;
	ray->is_facing_right = ray->angle < M_PI_2 || ray->angle > 3 * M_PI_2;
	ray->is_facing_left = !ray->is_facing_right;

	x_inter = floor(game->player.x / TILE_SIZE) * TILE_SIZE;
	x_inter += ray->is_facing_right ? TILE_SIZE : 0;
	y_inter = game->player.y + (x_inter - game->player.x) * tan(ray->angle);

	x_step = TILE_SIZE;
	x_step *= ray->is_facing_left ? -1 : 1;
	y_step = TILE_SIZE * tan(ray->angle);
	y_step *= (ray->is_facing_up && y_step > 0) ? -1 : 1;
	y_step *= (ray->is_facing_down && y_step < 0) ? -1 : 1;

	double next_hor_x = x_inter;
	double next_hor_y = y_inter;

	while (next_hor_x >= 0 && next_hor_x <= WIDTH && next_hor_y >= 0 && next_hor_y <= HEIGHT)
	{
		double x_tocheck = next_hor_x + (ray->is_facing_left ? -1 : 0);
		double y_tocheck = next_hor_y;
		if (hit_wall(game, x_tocheck, y_tocheck))
		{
			ray->hor_wall_hit_x = x_tocheck;
			ray->hor_wall_hit_y = y_tocheck;
			// hor_wall_content = game->map[(int)floor(y_tocheck / TILE_SIZE)][(int)floor(x_tocheck / TILE_SIZE)];
			// found_hor_wall_hit = true;
			break ;
		}
		else
		{
			next_hor_x += x_step;
			next_hor_y += y_step;
		}
	}
	return (sqrt(pow(ray->hor_wall_hit_x - game->player.x, 2) + pow(ray->hor_wall_hit_y - game->player.y, 2)));
}

double	get_horz_dis(t_game *game, t_ray *ray)
{
	double	x_inter;
	double	y_inter;
	double	x_step;
	double	y_step;
	// int hor_wall_content = 0;
	// bool found_hor_wall_hit = false;

	ray->is_facing_down = ray->angle > 0 && ray->angle < M_PI;
	ray->is_facing_up = !ray->is_facing_down;
	ray->is_facing_right = ray->angle < M_PI_2 || ray->angle > 3 * M_PI_2;
	ray->is_facing_left = !ray->is_facing_right;

	y_inter = floor(game->player.y / TILE_SIZE) * TILE_SIZE;
	y_inter += ray->is_facing_down ? TILE_SIZE : 0;
	x_inter = game->player.x + (y_inter - game->player.y) / tan(ray->angle);

	y_step = TILE_SIZE;
	y_step *= ray->is_facing_up ? -1 : 1;
	x_step = TILE_SIZE / tan(ray->angle);
	x_step *= (ray->is_facing_left && x_step > 0) ? -1 : 1;
	x_step *= (ray->is_facing_right && x_step < 0) ? -1 : 1;

	double next_hor_x = x_inter;
	double next_hor_y = y_inter;

	while (next_hor_x >= 0 && next_hor_x <= WIDTH && next_hor_y >= 0 && next_hor_y <= HEIGHT)
	{
		double x_tocheck = next_hor_x;
		double y_tocheck = next_hor_y + (ray->is_facing_up ? -1 : 0);
		if (hit_wall(game, x_tocheck, y_tocheck))
		{
			ray->hor_wall_hit_x = x_tocheck;
			ray->hor_wall_hit_y = y_tocheck;
			// hor_wall_content = game->map[(int)floor(y_tocheck / TILE_SIZE)][(int)floor(x_tocheck / TILE_SIZE)];
			// found_hor_wall_hit = true;
			break ;
		}
		else
		{
			next_hor_x += x_step;
			next_hor_y += y_step;
		}
	}
	return (sqrt(pow(ray->hor_wall_hit_x - game->player.x, 2) + pow(ray->hor_wall_hit_y - game->player.y, 2)));
}

double	norm_angle(t_ray *ray)
{
	ray->angle = fmod(ray->angle, 2 * M_PI);
	if (ray->angle < 0)
		ray->angle += 2 * M_PI;
	return (ray->angle);
}

void	render_ray(t_game *game, double angle, double distance)
{
	double	x = game->player.x;
	double	y = game->player.y;
	double	step = 1.0;

	double	x_step = cos(angle) * step;
	double	y_step = sin(angle) * step;
	while (distance > 0)
	{
		mlx_put_pixel(game->img, (int)x, (int)y, 0xFFFF00FF);
		x += x_step;
		y += y_step;
		distance -= step;
	}
}

void	render_wall(t_game *game, int column, double wall_bottom, double wall_height)
{
	double	wall_top;
	int		y;

	wall_top = (HEIGHT / 2) - (wall_height / 2);
	if (wall_top < 0)
		wall_top = 0;
	if (wall_bottom >= HEIGHT)
		wall_bottom = HEIGHT - 1;
	y = (int)wall_top;
	while (y <= (int)wall_bottom)
	{
		mlx_put_pixel(game->img, column, y, 0x000000);
		y++;
	}
}

void	render_floor(t_game *game, int column, double wall_bottom)
{
	int	y;

	y = wall_bottom;
	while (y < HEIGHT)
	{
		mlx_put_pixel(game->img, column, y, 0x80808080);
		y++;
	}
}

void	render_ceiling(t_game *game, int column, double wall_height)
{
	double	screen_bottom;
	int	y;

	y = 0;
	screen_bottom = (HEIGHT / 2) - (wall_height / 2);
	while (y < screen_bottom)
	{
		mlx_put_pixel(game->img, column, y, 0xFFFFFF);
		y++;
	}
}

void	cast_ray(t_game *game, t_ray *ray, int column)
{
	double distance;
	double wall_height;
	double wall_bottom;

	ray->horz = get_horz_dis(game, ray);
	ray->vert = get_vert_dis(game, ray);
	// if (ray->horz < ray->vert)
	// 	render_ray(game, ray->angle, ray->horz);
	// else
	// 	render_ray(game, ray->angle, ray->vert);
	if (ray->horz < ray->vert)
		distance = ray->horz;
	else
		distance = ray->vert;

	distance *= cos(ray->angle - game->player.angle);
	wall_height = (TILE_SIZE * (WIDTH / 2) / tan(FOV / 2)) / distance;
	wall_bottom = (HEIGHT / 2) + (wall_height / 2);
	render_wall(game, column, wall_bottom, wall_height);
	render_floor(game, column, wall_bottom);
	render_ceiling(game, column, wall_height);
}

void	ft_raycast(t_game *game)
{
	int		i;
	t_ray	ray;

	ray.angle = game->player.angle - FOV / 2;
	i = 0;
	while (i < WIDTH)
	{
		ray.angle = norm_angle(&ray);
		cast_ray(game, &ray, i);
		ray.angle += FOV / WIDTH;
		i++;
	}
}

