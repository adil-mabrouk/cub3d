/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 01:31:51 by amabrouk          #+#    #+#             */
/*   Updated: 2024/11/11 13:42:08 by amabrouk         ###   ########.fr       */
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

double	get_horz_dis(t_game *game, t_ray *ray)
{
	double	x_inter;
	double	y_inter;
	double	x_step;
	double	y_step;
	// int hor_wall_content = 0;
	bool found_hor_wall_hit = false;

	ray->is_facing_down = ray->angle > 0 && ray->angle < M_PI;
	ray->is_facing_up = !ray->is_facing_down;
	ray->is_facing_right = ray->angle < M_PI_2 || ray->angle > 3 * M_PI_2;
	ray->is_facing_left = !ray->is_facing_right;

	y_inter = floor(game->player.y / TILE_SIZE) * TILE_SIZE;
	y_inter += ray->is_facing_down ? TILE_SIZE : 0;
	x_inter = game->player.x + (y_inter - game->player.y) / tan(ray->angle);

	y_step = TILE_SIZE;
	y_step += ray->is_facing_up ? -1 : 1;
	x_step = TILE_SIZE / tan(ray->angle);
	x_step *= (ray->is_facing_left && x_step > 0) ? -1 : 1;
	x_step *= (ray->is_facing_right && x_step < 0) ? -1 : 1;

	double next_hor_x = x_inter;
	double next_hor_y = y_inter;

	while (next_hor_x >= 0 && next_hor_x <= WIDTH && next_hor_y >= 0 && next_hor_y <= HEIGHT)
	{
		// double x_tocheck = next_hor_x;
		// double y_tocheck = next_hor_y + ray->is_facing_up ? 1 : 0;
		if (hit_wall(game, next_hor_x, next_hor_y))
		{
			ray->hor_wall_hit_x = next_hor_x;
			ray->hor_wall_hit_y = next_hor_y;
			// hor_wall_content = game->map[(int)floor(y_tocheck / TILE_SIZE)][(int)floor(x_tocheck / TILE_SIZE)];
			found_hor_wall_hit = true;
			break ;
		}
		else
		{
			next_hor_x += x_step;
			next_hor_y += y_step;
		}
	}
	if (found_hor_wall_hit)
		return (sqrt(pow(ray->hor_wall_hit_x - game->player.x, 2) + pow(ray->hor_wall_hit_y - game->player.y, 2)));
	return 0;
}

double	norm_angle(t_ray *ray)
{
	ray->angle = fmod(ray->angle, 2 * M_PI);
	if (ray->angle < 0)
		ray->angle += 2 * M_PI;
	return (ray->angle);
}

void	render_ray(t_game *game, t_ray *ray)
{
	double	x = game->player.x;
	double	y = game->player.y;
	double	step = 1.0; // Step size, can be adjusted based on your precision needs
	// int		color = 0xFFFF00; // Yellow color for the ray
	int	dist = ray->horz; // This should be the distance to the hit point

	// Calculate steps in the direction of the ray
	double	x_step = cos(ray->angle) * step;
	double	y_step = sin(ray->angle) * step;

	// Draw each step from the player to the wall hit point
	while (dist > 2)
	{
		mlx_put_pixel(game->img, (int)x, (int)y, 0xFFFF00FF);
		x += x_step;
		y += y_step;
		dist -= step; // Decrease distance to stop when we reach the wall
	}
}

void	cast_ray(t_game *game, t_ray *ray, int i)
{
	(void)i;
	dprintf(2, "ray_angle = %f\n", ray->angle);
	ray->horz = get_horz_dis(game, ray);
	// dprintf(2, "%d/n", ray->horz);
	// v_inter = get_vert_dis();
	render_ray(game, ray);
}

void	init_ray(t_ray *ray)
{
	ray->angle = 0;
	ray->hor_wall_hit_x = 0.0;
	ray->hor_wall_hit_y = 0.0;
	ray->horz = 0;
	ray->is_facing_down = -1;
	ray->is_facing_up = -1;
	ray->is_facing_left = -1;
	ray->is_facing_right = -1;
}

void	ft_raycast(t_game *game)
{
	int		i;
	t_ray	ray;

	ray.angle = game->player.angle - FOV / 2;
	ray.angle = norm_angle(&ray);
	// dprintf(2, "Angle ray == %f\n", ray.angle);
	i = 0;
	while (i < WIDTH)
	{
		// dprintf(2, "i = %d\n", i);
		cast_ray(game, &ray, i);
		ray.angle += FOV / WIDTH;
		i++;
	}
}

