#include "cub3d.h"

void	draw_map(t_game *game)
{
	int r = -1;
	int	col;

	while (++r < game->rows)
	{
		col = -1;
		while (++col < game->colums)
		{
			int tile = game->map[r][col];
			int x = col * game->tile_size;
			int y = r * game->tile_size;
			int color = tile == 1 ? 0x000000FF : 0x0000FF00;
			int i = -1;
			while (++i < game->tile_size)
			{
				int j = -1;
				while (++j < game->tile_size)
					mlx_put_pixel(game->img, x + i, y + j, color);
			}
		}
	}
}

void	draw_line(t_game *game, int x0, int y0, int x1, int y1)
{
	float	dx = x1 - x0;
	float	dy = y1 - y0;
	int	steps = fabsf(dx) > fabsf(dy) ? fabsf(dx) : fabsf(dy); // Determine the number of steps

	float	x_inc = dx / steps; // Calculate the increment in x for each step
	float	y_inc = dy / steps; // Calculate the increment in y for each step

	float	x = x0;
	float	y = y0;

	for (int i = 0; i <= steps; i++)
	{
		mlx_put_pixel(game->img, x, y, 0xFFFF00FF); // Plot the pixel
		x += x_inc; // Increment x-coordinate by x_inc
		y += y_inc; // Increment y-coordinate by y_inc
	}
}

void	draw_player(t_game *game, int line_length)
{
	int i = -game->player.radius;
	while (++i < game->player.radius)
	{
		int	j = -game->player.radius;
		while (++j < game->player.radius)
			if (i * i + j * j <= game->player.radius * game->player.radius)
				mlx_put_pixel(game->img, game->player.x + i, game->player.y + j, 0xFF0000FF);
	}
	int	line_x = game->player.x + line_length * cos(game->player.angle);
	int	line_y = game->player.y + line_length * sin(game->player.angle);
	draw_line(game, game->player.x, game->player.y, line_x, line_y);
}

int	has_wall(t_game *game, double	new_x, double	new_y)
{
	double x = new_x -10;
	double y;
	int	grid_x;
	int	grid_y;

	while (x <= new_x + 10)
	{
		y = new_y - 10;
		while (y <= new_y + 10)
		{
			grid_x = x / game->tile_size;
			grid_y = y / game->tile_size;
			if (game->map[grid_y][grid_x] == 1)
				return 1;
			y++;
		}
		x++;
	}
	game->player.x = new_x;
	game->player.y = new_y;
	return 0;
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game		*game;
	t_player	*player;

	game = (t_game *)param;
	player = &game->player;
	if (keydata.key == MLX_KEY_W && keydata.action == 1 && !has_wall(game, player->x + 2 * cos(player->angle), player->y + 2 * sin(player->angle)))
	{
		player->x += 2 * cos(player->angle);
		player->y += 2 * sin(player->angle);
	}
	else if (keydata.key == MLX_KEY_S && keydata.action == 1 && !has_wall(game, player->x - 2 * cos(player->angle), player->y - 2 * sin(player->angle)))
	{
		player->x -= 2 * cos(player->angle);
		player->y -= 2 * sin(player->angle);
	}
	else if (keydata.key == MLX_KEY_A && keydata.action == 1 && !has_wall(game, player->x - 2 * cos(player->angle + M_PI_2), player->y - 2 * sin(player->angle + M_PI_2)))
	{
		player->x -= 2 * cos(player->angle + M_PI_2);
		player->y -= 2 * sin(player->angle + M_PI_2);
	}
	else if (keydata.key == MLX_KEY_D && keydata.action == 1 && !has_wall(game, player->x + 2 * cos(player->angle + M_PI_2), player->y + 2 * sin(player->angle + M_PI_2)))
	{
		player->x += 2 * cos(player->angle + M_PI_2);
		player->y += 2 * sin(player->angle + M_PI_2);
	}
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == 1)
		player->angle -= M_PI / 12;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == 1)
		player->angle += M_PI / 12;
	else
		return ;
	mlx_delete_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, game->width, game->height);
	draw_map(game);
	draw_player(game, 40);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}

void	init_game(t_game *game)
{
	int temp_map[15][20] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 20; j++)
			game->map[i][j] = temp_map[i][j];
	game->tile_size = 32;
	game->rows = 15;
	game->colums = 20;
	game->width = (game->tile_size * game->colums);
	game->height = (game->tile_size * game->rows);
	game->player.x = (game->width / 2);
	game->player.y = (game->height / 2);
	game->player.radius = 10;
	game->player.angle = 0;
	game->mlx = mlx_init(game->width, game->height, "Adil's Map", true);
}

int main()
{
	t_game	game;
	init_game(&game);
	game.img = mlx_new_image(game.mlx, game.width, game.height);
	draw_map(&game);
	draw_player(&game, 40);
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return 0;
}