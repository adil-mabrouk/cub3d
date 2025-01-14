/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: i61mail <i61mail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 01:31:51 by amabrouk          #+#    #+#             */
/*   Updated: 2025/01/14 15:45:08 by i61mail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hit_wall(t_game *game, double x, double y)
{
	int tile_x = floor(x / TILE_SIZE);
	int tile_y = floor(y / TILE_SIZE);
	if (game->pars->map[tile_y][tile_x] != 48)
		return 1;
	return 0;
}

double get_vert_dis(t_game *game, t_ray *ray)
{
    double x_inter, y_inter, x_step, y_step;
    double next_x, next_y;
    double dist = INFINITY;

    x_inter = floor(game->player.x / TILE_SIZE) * TILE_SIZE;
    if (ray->is_facing_right)
        x_inter += TILE_SIZE;
        
    y_inter = game->player.y + (x_inter - game->player.x) * tan(ray->angle);
    
    if (ray->is_facing_left)
        x_step = TILE_SIZE * (-1);
    else
        x_step = TILE_SIZE;
        
    y_step = TILE_SIZE * tan(ray->angle);
    
    if (ray->is_facing_up && y_step > 0)
        y_step *= -1;
    if (ray->is_facing_down && y_step < 0)
        y_step *= -1;
        
    next_x = x_inter;
    next_y = y_inter;
    
    while (next_x >= 0 && next_x <= WIDTH && next_y >= 0 && next_y <= HEIGHT)
    {
        double x_tocheck;
        if (ray->is_facing_left)
            x_tocheck = next_x - 1;
        else
            x_tocheck = next_x;
            
        double y_tocheck = next_y;
        
        if (hit_wall(game, x_tocheck, y_tocheck))
        {
            ray->vert_wall_hit_x = next_x;
            ray->vert_wall_hit_y = next_y;
            dist = sqrt(pow(next_x - game->player.x, 2) + pow(next_y - game->player.y, 2));
            break;
        }
        next_x += x_step;
        next_y += y_step;
    }
    return dist;
}

double get_horz_dis(t_game *game, t_ray *ray)
{
    double x_inter, y_inter, x_step, y_step;
    double next_x, next_y;
    double dist = INFINITY;
    
    ray->is_facing_down = ray->angle > 0 && ray->angle < M_PI;
    ray->is_facing_up = !ray->is_facing_down;
    ray->is_facing_right = ray->angle < M_PI_2 || ray->angle > 3 * M_PI_2;
    ray->is_facing_left = !ray->is_facing_right;
    
    y_inter = floor(game->player.y / TILE_SIZE) * TILE_SIZE;
    if (ray->is_facing_down)
        y_inter += TILE_SIZE;
        
    x_inter = game->player.x + (y_inter - game->player.y) / tan(ray->angle);
    
    y_step = TILE_SIZE;
    if (ray->is_facing_up)
        y_step *= -1;
        
    x_step = TILE_SIZE / tan(ray->angle);
    
    if (ray->is_facing_left && x_step > 0)
        x_step *= -1;
    if (ray->is_facing_right && x_step < 0)
        x_step *= -1;
        
    next_x = x_inter;
    next_y = y_inter;
    
    while (next_x >= 0 && next_x <= WIDTH && next_y >= 0 && next_y <= HEIGHT)
    {
        double x_tocheck = next_x;
        double y_tocheck;
        if (ray->is_facing_up)
            y_tocheck = next_y - 1;
        else
            y_tocheck = next_y;
            
        if (hit_wall(game, x_tocheck, y_tocheck))
        {
            ray->hor_wall_hit_x = next_x;
            ray->hor_wall_hit_y = next_y;
            dist = sqrt(pow(next_x - game->player.x, 2) + pow(next_y - game->player.y, 2));
            break;
        }
        next_x += x_step;
        next_y += y_step;
    }
    return dist;
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

void cast_ray(t_game *game, t_ray *ray, int column)
{
    double distance;
    double wall_height;
    double wall_bottom;

    ray->horz = get_horz_dis(game, ray);
    ray->vert = get_vert_dis(game, ray);
    if (ray->horz == INFINITY && ray->vert == INFINITY)
        distance = INFINITY;
    else if (ray->horz == INFINITY)
        distance = ray->vert;
    else if (ray->vert == INFINITY)
        distance = ray->horz;
    else
    {
        if (ray->horz < ray->vert)
            distance = ray->horz;
        else
            distance = ray->vert;
    }
    if (distance == INFINITY || distance < 0.1)
        distance = 0.1;
    //lprob d fisheye effect, kaybano l7youta mlwyin wla ma3rt
    distance *= cos(ray->angle - game->player.angle);
    wall_height = (TILE_SIZE * (WIDTH / 2) / tan(FOV / 2)) / distance;
    wall_bottom = (HEIGHT / 2) + (wall_height / 2);
    render_textured_wall(game, ray, column, wall_height);
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

