/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:16:02 by amabrouk          #+#    #+#             */
/*   Updated: 2025/01/25 20:55:23 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_player(t_game *game, int px, int py, int ray)
{
	int	i;
	int	j;
	int	dx;
	int	dy;

	i = px - ray - 1;
	while (++i <= px + ray)
	{
		j = py - ray - 1;
		while (++j <= py + ray)
		{
			dx = i - px;
			dy = j - py;
			if (dx * dx + dy * dy <= ray * ray)
			{
				mlx_put_pixel(game->mini_map, i, j, get_rgb(255, 0, 0));
			}
		}
	}
}

int	collide_with_wall(t_game *game, double new_x, double new_y)
{
	if (hit_wall(game, new_x, game->pars->player.y)) //horizental
		new_x = game->pars->player.x; // kan usi lblasa nit d 'y' bach ntchecki biha ghir 'x' rasha
	if (hit_wall(game, game->pars->player.x, new_y)) //vertical
		new_y = game->pars->player.y; // kan usi lblasa nit d 'x' bach ntchecki biha ghir 'y' rasha
	if (hit_wall(game, new_x, new_y))
		return (1);
	game->pars->player.x = new_x;
	game->pars->player.y = new_y;
	return (0);
}

void	handle_door(t_game *game)
{
	double	check_x;
	double	check_y;
	int		tile_x;
	int		tile_y;

	check_x = game->pars->player.x + cos(game->pars->player.angle) * TILE_SIZE;
	check_y = game->pars->player.y + sin(game->pars->player.angle) * TILE_SIZE;
	tile_x = floor(check_x / TILE_SIZE);
	tile_y = floor(check_y / TILE_SIZE);
	if (tile_y >= 0 && tile_y < game->pars->len_rows
		&& tile_x >= 0 && tile_x < game->pars->len_columns)
	{
		if (mlx_is_key_down(game->mlx, MLX_KEY_O)
			&& game->pars->map[tile_y][tile_x] == 'D')
		{
			game->pars->map[tile_y][tile_x] = DOOR_OPEN;
		}
		else if (mlx_is_key_down(game->mlx, MLX_KEY_C)
			&& game->pars->map[tile_y][tile_x] == DOOR_OPEN)
		{
			game->pars->map[tile_y][tile_x] = 'D';
		}
	}
}

void	handle_keys(t_game *game)
{
	t_player	*player;

	player = &game->pars->player;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		mlx_terminate(game->mlx);
		exit(0);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		collide_with_wall(game, player->x + SPEED * cos(player->angle),
			player->y + SPEED * sin(player->angle));
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		collide_with_wall(game, player->x - SPEED * cos(player->angle),
			player->y - SPEED * sin(player->angle));
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		collide_with_wall(game, player->x - SPEED * cos(player->angle + M_PI_2),
			player->y - SPEED * sin(player->angle + M_PI_2));
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		collide_with_wall(game, player->x + SPEED * cos(player->angle + M_PI_2),
			player->y + SPEED * sin(player->angle + M_PI_2));
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		player->angle -= M_PI / 60.0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		player->angle += M_PI / 60.0;
	handle_door(game);
}

void	mouse_hook(double curr_x_pos, double curr_y_pos, void *param)
{
	static double	last_x_pos;
	double			delta_x;
	t_game			*game;

	(void)curr_y_pos;
	game = (t_game *)param;
	last_x_pos = 0;
	delta_x = curr_x_pos - last_x_pos; // kan7seb delta d lmouse bach n3ref chhal dart lmouse 3la fin kant 9bel hadik hya delta
	game->pars->player.angle += delta_x * 0.005; // hna kanbdel lih l angel b delta li 7sebt w sor3a bach ghaydor
	last_x_pos = curr_x_pos; // akhir pos kan fiha kanstoriha
}

void	clear_img(mlx_image_t *img)
{
	int	y;
	int	x;

	y = -1;
	while (++y < (int)img->height)
	{
		x = -1;
		while (++x < (int)img->width)
			mlx_put_pixel(img, x, y, get_rgb(255, 255, 255));
	}
}

void	loop_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_keys(game);
	clear_img(game->img);
	ft_raycast(game);
	render_sprite(game);
}

void	load_texture(mlx_texture_t **texture, char *path)
{
	*texture = mlx_load_png(path);
	if (!*texture)
	{
		ft_putstr_fd("Error loading texture\n", 2);
		exit(1);
	}
}

void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_Y && keydata.action == MLX_PRESS)
		game->sprite.show_sprite = !game->sprite.show_sprite;
}

void	x_button(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_terminate(game->mlx);
	exit(0);
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "Map", true);
	mlx_close_hook(game->mlx, &x_button, game);
	if (!game->mlx)
	{
		ft_putstr_fd("Error init mlx\n", 2);
		exit(1);
	}
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->mini_map = mlx_new_image(game->mlx, MINI_MAP_WIDTH, MINI_MAP_HEIGHT);
	game->width = game->pars->len_columns * TILE_SIZE;
	game->height = game->pars->len_rows * TILE_SIZE;
	load_texture(&game->textures.north, game->pars->north);
	load_texture(&game->textures.south, game->pars->south);
	load_texture(&game->textures.east, game->pars->east);
	load_texture(&game->textures.west, game->pars->west);
	load_texture(&game->textures.door,);
	init_sprite(game);
}
