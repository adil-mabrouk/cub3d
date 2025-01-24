/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:17:19 by amabrouk          #+#    #+#             */
/*   Updated: 2025/01/24 19:28:10 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	hit_wall(t_game *game, double x, double y)
{
	int tile_x = floor(x / TILE_SIZE);
	int tile_y = floor(y / TILE_SIZE);
	if (x < 0 || x >= game->width || y < 0 || y >= game->height)
		return 1;
	else if (tile_y < 0 || tile_y >= game->pars->len_rows || tile_x < 0 || tile_x >= game->pars->len_columns)
		return 1;
	else if (game->pars->map[tile_y][tile_x] == '1' || game->pars->map[tile_y][tile_x] == 'D')
        return 1;
	return 0;
}

double get_vert_dis(t_game *game, t_ray *ray)
{
    double x_inter, y_inter, x_step, y_step;
    double next_x, next_y;

    x_inter = floor(game->pars->player.x / TILE_SIZE) * TILE_SIZE;
    if (ray->is_facing_right)
        x_inter += TILE_SIZE;
        
    y_inter = game->pars->player.y + (x_inter - game->pars->player.x) * tan(ray->angle);
    
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
    
    while (next_x >= 0 && next_x <= game->width && next_y >= 0 && next_y <= game->height)
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
            break;
        }
        next_x += x_step;
        next_y += y_step;
    }
    return sqrt(pow(next_x - game->pars->player.x, 2) + pow(next_y - game->pars->player.y, 2));
}

double get_horz_dis(t_game *game, t_ray *ray)
{
    double x_inter, y_inter, x_step, y_step;
    double next_x, next_y;
    
    ray->is_facing_down = ray->angle > 0 && ray->angle < M_PI;
    ray->is_facing_up = !ray->is_facing_down;
    ray->is_facing_right = ray->angle < M_PI_2 || ray->angle > 3 * M_PI_2;
    ray->is_facing_left = !ray->is_facing_right;
    
    y_inter = floor(game->pars->player.y / TILE_SIZE) * TILE_SIZE;
    if (ray->is_facing_down)
        y_inter += TILE_SIZE;
        
    x_inter = game->pars->player.x + (y_inter - game->pars->player.y) / tan(ray->angle);
    
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
    
    while (next_x >= 0 && next_x <= game->width && next_y >= 0 && next_y <= game->height)
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
            break;
        }
        next_x += x_step;
        next_y += y_step;
    }
    return sqrt(pow(next_x - game->pars->player.x, 2) + pow(next_y - game->pars->player.y, 2));;
}

double	norm_angle(t_ray *ray)
{
	ray->angle = fmod(ray->angle, 2 * M_PI);
	if (ray->angle < 0)
		ray->angle += 2 * M_PI;
	return (ray->angle);
}

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
	int	y;

	y = 0;
	screen_bottom = (HEIGHT / 2) - (wall_height / 2);
	while (y < screen_bottom)
	{
		mlx_put_pixel(game->img, column, y, game->pars->c_color);
		y++;
	}
}

int    get_color(t_game *game, int x, int y)
{
    if (y > 0 && x > 0)
    {
        x /= TILE_SIZE;
        y /= TILE_SIZE;
        if (game->pars->map[y][x] == '1')
            return (create_rgb(128,128,128));
        else if (game->pars->map[y][x] == 'D')
            return (create_rgb(0,0,255));
        else if (game->pars->map[y][x] == '0')
            return (create_rgb(255,255,255));
    }
    return (create_rgb(128,128,128));
}

bool    ftt_check(t_game *game, int x, int y)
{
    if (y > 0 && x > 0 && y < game->pars->len_rows * TILE_SIZE && x < game->pars->len_columns * TILE_SIZE)
        return (true);
    return (false);
}

int	render_minimap(t_game *game)
{
	int y_i = -1;
    // double r = 160.0 / (TILE_SIZE * 5);
    int y = ((int)ceil(game->pars->player.y) - TILE_SIZE * 2.5) - 1;
	while (++y_i < (TILE_SIZE * 5) && ++y >= INT_MIN)
	{
		int x = ((int)ceil(game->pars->player.x) - TILE_SIZE * 2.5) - 1;
		int x_i = -1;
		while (++x_i < (TILE_SIZE * 5) && ++x >= INT_MIN)
		{
            int f = ftt_check(game, x, y);
			if (f && (game->pars->map[y / TILE_SIZE][x / TILE_SIZE] == '1'))
				mlx_put_pixel(game->mini_map, x_i, y_i, create_rgb(0, 0, 255));
			else if (f && game->pars->map[y / TILE_SIZE][x / TILE_SIZE] == 'D')
				mlx_put_pixel(game->mini_map, x_i, y_i, create_rgb(128, 0, 0));
			else if (f && game->pars->map[y / TILE_SIZE][x / TILE_SIZE] == 'O')
				mlx_put_pixel(game->mini_map, x_i, y_i, create_rgb(255, 255, 255));
			else
            {
                // if (f && x <= 200)
                //     printf("x: %d, y: %d -> char: %c\n", x, y, game->pars->map[y / TILE_SIZE][x / TILE_SIZE]);
				mlx_put_pixel(game->mini_map, x_i, y_i, create_rgb(0, 0, 0));
            }
		}
	}
    draw_player(game, MINI_MAP_WIDTH / 2, MINI_MAP_HEIGHT / 2, 4);
	return (1);
}

void cast_ray(t_game *game, t_ray *ray, int column)
{
    double distance;
    double wall_height;
    double wall_bottom;

    ray->horz = get_horz_dis(game, ray);
    ray->vert = get_vert_dis(game, ray);
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
	int		i;
	t_ray	ray;

	ray.angle = game->pars->player.angle - FOV / 2;
	i = 0;
	while (i < WIDTH)
	{
		ray.angle = norm_angle(&ray);
		cast_ray(game, &ray, i);
		ray.angle += FOV / WIDTH;
		i++;
	}
    render_minimap(game);
}
