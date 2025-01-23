/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:30:08 by isrkik            #+#    #+#             */
/*   Updated: 2025/01/23 18:46:07 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_frame_counter(t_game *game)
{
	if (game->sprite.show_sprite)
	{
		game->sprite.frame_counter++;
		if (game->sprite.frame_counter >= 4)
		{
			game->sprite.current_frame = (game->sprite.current_frame + 1) % 10;
			game->sprite.frame_counter = 0;
		}
	}
}

void	draw_sprite_texture(t_game *game, unsigned int max_height,
		unsigned int max_width, float scaling)
{
	uint32_t	pixel_offset;
	uint8_t		*pixel;
	uint32_t	color;
	int			screen_x;
	int			screen_y;

	if (game->sprite.tex_x < game->sprite.current->width
		&& game->sprite.tex_y < game->sprite.current->height)
	{
		pixel_offset = (game->sprite.tex_y * game->sprite.current->width
				+ game->sprite.tex_x) * 4;
		pixel = &game->sprite.current->pixels[pixel_offset];
		if (pixel[3] > 0)
		{
			color = (pixel[0] << 24) | (pixel[1] << 16)
				| (pixel[2] << 8) | pixel[3];
			screen_x = game->sprite.x + (WIDTH / 2) - (max_width / 2);
			screen_y = game->sprite.y + (HEIGHT - ((game->sprite.current->height
							* scaling) / 2)) - (max_height / 2);
			if (screen_x >= 0 && screen_x < WIDTH
				&& screen_y >= 0 && screen_y < HEIGHT)
				mlx_put_pixel(game->img, screen_x, screen_y, color);
		}
	}
}

void	render_sprite(t_game *game)
{
	float			scaling;
	unsigned int	max_height;
	unsigned int	max_width;

	scaling = 0.6;
	if (!game || !game->img || !game->sprite.frames[game->sprite.current_frame] || !game->sprite.show_sprite)
		return ;
	game->sprite.current = game->sprite.frames[game->sprite.current_frame];
	max_height = game->sprite.current->height * scaling;
	max_width = game->sprite.current->width * scaling;
	game->sprite.y = 0;
	while (game->sprite.y < max_height)
	{
		game->sprite.x = 0;
		while (game->sprite.x < max_width)
		{
			game->sprite.tex_x = game->sprite.x / scaling;
			game->sprite.tex_y = game->sprite.y / scaling;
			draw_sprite_texture(game, max_height, max_width, scaling);
			game->sprite.x++;
		}
		game->sprite.y++;
	}
	update_frame_counter(game);
}

void	init_sprite(t_game *game)
{
	int	i;

	i = 0;
	game->sprite.frames[0] = mlx_load_png("/home/isrkik/Desktop/cub3d\
/bonus/parsing_bonus/textures_bonus/frames/frame1.png");
	game->sprite.frames[1] = mlx_load_png("/home/isrkik/Desktop/cub3d\
/bonus/parsing_bonus/textures_bonus/frames/frame2.png");
	game->sprite.frames[2] = mlx_load_png("/home/isrkik/Desktop/cub3d\
/bonus/parsing_bonus/textures_bonus/frames/frame3.png");
	game->sprite.frames[3] = mlx_load_png("/home/isrkik/Desktop/cub3d\
/bonus/parsing_bonus/textures_bonus/frames/frame4.png");
	game->sprite.frames[4] = mlx_load_png("/home/isrkik/Desktop/cub3d\
/bonus/parsing_bonus/textures_bonus/frames/frame5.png");
	game->sprite.frames[5] = mlx_load_png("/home/isrkik/Desktop/cub3d\
/bonus/parsing_bonus/textures_bonus/frames/frame6.png");
	game->sprite.frames[6] = mlx_load_png("/home/isrkik/Desktop/cub3d\
/bonus/parsing_bonus/textures_bonus/frames/frame7.png");
	game->sprite.frames[7] = mlx_load_png("/home/isrkik/Desktop/cub3d\
/bonus/parsing_bonus/textures_bonus/frames/frame8.png");
	game->sprite.frames[8] = mlx_load_png("/home/isrkik/Desktop/cub3d\
/bonus/parsing_bonus/textures_bonus/frames/frame9.png");
	game->sprite.frames[9] = mlx_load_png("/home/isrkik/Desktop/cub3d\
/bonus/parsing_bonus/textures_bonus/frames/frame10.png");
	while (i < 10)
	{
		if (!game->sprite.frames[i])
		{
			printf("Error loading sprite texture %d\n", i);
			exit(1);
		}
		i++;
	}
	game->sprite.current_frame = 0;
	game->sprite.frame_counter = 0;
	game->sprite.show_sprite = false;
}
