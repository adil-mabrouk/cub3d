/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:16:44 by amabrouk          #+#    #+#             */
/*   Updated: 2025/01/17 13:16:45 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void get_wall_texture(t_game *game, t_ray *ray, double *tex_x)
{
    double hit_x;

    if (!game || !ray || !game->textures.north || !game->textures.south || 
        !game->textures.east || !game->textures.west)
    {
        ray->wall_texture = NULL;
        return;
    }

    if (ray->horz < ray->vert)
    {
        hit_x = ray->hor_wall_hit_x;

        if (ray->is_facing_up)
            ray->wall_texture = game->textures.north;
        else
            ray->wall_texture = game->textures.south;

        *tex_x = fmod(hit_x, TILE_SIZE) * (ray->wall_texture->width / TILE_SIZE);
    }
    else
    {
        hit_x = ray->vert_wall_hit_x;
        if (ray->is_facing_right)
            ray->wall_texture = game->textures.east;
        else
            ray->wall_texture = game->textures.west;

        *tex_x = fmod(ray->vert_wall_hit_y, TILE_SIZE) * (ray->wall_texture->width / TILE_SIZE);
    }
}


void render_textured_wall(t_game *game, t_ray *ray, int column, double wall_height)
{
    double wall_top = (HEIGHT / 2) - (wall_height / 2);
    double wall_bottom = (HEIGHT / 2) + (wall_height / 2);
    double tex_x, tex_y = 0.0, tex_y_step;

    if (wall_top < 0)
        wall_top = 0;
    if (wall_bottom >= HEIGHT)
        wall_bottom = HEIGHT - 1;
    get_wall_texture(game, ray, &tex_x);
    if (!ray->wall_texture || !ray->wall_texture->pixels)
    {
        int y = wall_top;
        while (y < wall_bottom)
        {
            mlx_put_pixel(game->img, column, y, 0x808080FF);
            y++;
        }
        return;
    }
    tex_y_step = ray->wall_texture->height / wall_height;
    if (wall_height > HEIGHT)
    {
        tex_y = (wall_height - HEIGHT) / 2 * tex_y_step;
        wall_height = HEIGHT;
    }
    int y = wall_top;
    while (y < wall_bottom)
    {
        int tex_y_int = (int)tex_y % ray->wall_texture->height;
        if (tex_y_int < 0)
            tex_y_int = 0;
        int tex_index = (tex_y_int * ray->wall_texture->width + (int)tex_x) * 4;
        if (tex_index >= 0 && tex_index < (int)ray->wall_texture->width * (int)ray->wall_texture->height * 4)
        {
            uint8_t *pixel = &ray->wall_texture->pixels[tex_index];
            uint32_t color = (pixel[0] << 24) | (pixel[1] << 16) |
                            (pixel[2] << 8) | pixel[3];
            mlx_put_pixel(game->img, column, y, color);
        }
        tex_y += tex_y_step;
        y++;
    }
}

