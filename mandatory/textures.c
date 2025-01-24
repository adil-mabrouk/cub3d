/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:16:44 by amabrouk          #+#    #+#             */
/*   Updated: 2025/01/23 14:53:55 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_wall_texture(t_game *game, t_ray *ray, double *tex_x)
{
	double	hit_x;

	if (ray->horz < ray->vert)
	{
		hit_x = ray->hor_wall_hit_x;
		if (ray->is_facing_up)
			ray->wall_texture = game->textures.north;
		else
			ray->wall_texture = game->textures.south;
		*tex_x = fmod(hit_x, TILE_SIZE)
			* (ray->wall_texture->width / TILE_SIZE);
	}
	else
	{
		hit_x = ray->vert_wall_hit_x;
		if (ray->is_facing_right)
			ray->wall_texture = game->textures.east;
		else
			ray->wall_texture = game->textures.west;
		*tex_x = fmod(ray->vert_wall_hit_y, TILE_SIZE)
			* (ray->wall_texture->width / TILE_SIZE);
	}
}

void	draw_tex(t_ray *ray, t_game *game, int column, int y)
{
	uint8_t		*pixel;
	uint32_t	color;
	int			tex_index;
	int			tex_y_int;

	while (y < game->tex_utils.wall_bottom)
	{
		tex_y_int = (int)game->tex_utils.tex_y % ray->wall_texture->height;
		if (tex_y_int < 0)
			tex_y_int = 0;
		tex_index = (tex_y_int * ray->wall_texture->width
				+ (int)game->tex_utils.tex_x) * 4;
		if (tex_index >= 0 && tex_index < (int)ray->wall_texture->width
			* (int)ray->wall_texture->height * 4)
		{
			pixel = &ray->wall_texture->pixels[tex_index];
			color = (pixel[0] << 24) | (pixel[1] << 16)
				| (pixel[2] << 8) | pixel[3];
			mlx_put_pixel(game->img, column, y, color);
		}
		game->tex_utils.tex_y += game->tex_utils.tex_y_step;
		y++;
	}
}

void	render_textured_wall(t_game *game, t_ray *ray,
								int column, double wall_height)
{
	int	y;

	game->tex_utils.wall_top = (HEIGHT / 2) - (wall_height / 2);
	game->tex_utils.wall_bottom = (HEIGHT / 2) + (wall_height / 2);
	game->tex_utils.tex_y = 0.0;
	if (game->tex_utils.wall_top < 0)
		game->tex_utils.wall_top = 0;
	if (game->tex_utils.wall_bottom >= HEIGHT)
		game->tex_utils.wall_bottom = HEIGHT - 1;
	get_wall_texture(game, ray, &game->tex_utils.tex_x);
	game->tex_utils.tex_y_step = ray->wall_texture->height / wall_height;
	if (wall_height > HEIGHT)
	{
		game->tex_utils.tex_y = (wall_height - HEIGHT)
			/ 2 * game->tex_utils.tex_y_step;
		wall_height = HEIGHT;
	}
	y = game->tex_utils.wall_top;
	draw_tex(ray, game, column, y);
}
