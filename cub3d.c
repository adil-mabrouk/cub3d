#include "cub3d.h"

void	draw_map(t_game *game)
{
	int r = -1;
	int	col;

	while (++r < ROWS)
	{
		col = -1;
		while (++col < COLUMNS)
		{
			int tile = game->map[r][col];
			int x = col * TILE_SIZE;
			int y = r * TILE_SIZE;
			int color = tile == 1 ? 0x000000FF : 0x0000FF00;
			int i = -1;
			while (++i < TILE_SIZE)
			{
				int j = -1;
				while (++j < TILE_SIZE)
					mlx_put_pixel(game->img, x + i, y + j, color);
			}
		}
	}
}

void	draw_line(t_game *game, int x1, int y1, int color)
{
	double	dx = x1 - game->player.x;
	double	dy = y1 - game->player.y;
	int	steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy); // Determine the number of steps

	double	x_inc = dx / steps; // Calculate the increment in x for each step
	double	y_inc = dy / steps; // Calculate the increment in y for each step

	double	x = game->player.x;
	double	y = game->player.y;

	for (int i = 0; i <= steps; i++)
	{
		mlx_put_pixel(game->img, x, y, color); // Plot the pixel
		x += x_inc; // Increment x-coordinate by x_inc
		y += y_inc; // Increment y-coordinate by y_inc
	}
}

void	draw_player(t_game *game)
{
	int i = -game->player.radius;
	while (++i < game->player.radius)
	{
		int	j = -game->player.radius;
		while (++j < game->player.radius)
			if (i * i + j * j <= game->player.radius * game->player.radius)
				mlx_put_pixel(game->img, game->player.x + i, game->player.y + j, 0xFF0000FF);
	}
	// int	line_x = game->player.x + line_length * cos(game->player.angle);
	// int	line_y = game->player.y + line_length * sin(game->player.angle);
	// draw_line(game, line_x, line_y, 0xFFFF00FF);
	ft_raycast(game);
}

int	collision_with_wall(t_game *game, double new_x, double new_y)
{
	double x = new_x - 11;
	double y;
	int	grid_x;
	int	grid_y;

	while (x <= new_x + 11)
	{
		y = new_y - 11;
		while (y <= new_y + 11)
		{
			grid_x = x / TILE_SIZE;
			grid_y = y / TILE_SIZE;
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
	if (keydata.key == MLX_KEY_W && !collision_with_wall(game, player->x + 2 * cos(player->angle), player->y + 2 * sin(player->angle)))
	{
		player->x += 2 * cos(player->angle);
		player->y += 2 * sin(player->angle);
	}
	else if (keydata.key == MLX_KEY_S && !collision_with_wall(game, player->x - 2 * cos(player->angle), player->y - 2 * sin(player->angle)))
	{
		player->x -= 2 * cos(player->angle);
		player->y -= 2 * sin(player->angle);
	}
	else if (keydata.key == MLX_KEY_A && !collision_with_wall(game, player->x - 2 * cos(player->angle + M_PI_2), player->y - 2 * sin(player->angle + M_PI_2)))
	{
		player->x -= 2 * cos(player->angle + M_PI_2);
		player->y -= 2 * sin(player->angle + M_PI_2);
	}
	else if (keydata.key == MLX_KEY_D && !collision_with_wall(game, player->x + 2 * cos(player->angle + M_PI_2), player->y + 2 * sin(player->angle + M_PI_2)))
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
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	draw_map(game);
	draw_player(game);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}

void	init_game(t_game *game)
{
	int temp_map[ROWS][COLUMNS] = {
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

	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLUMNS; j++)
			game->map[i][j] = temp_map[i][j];
	game->player.x = (WIDTH / 2);
	game->player.y = (HEIGHT / 2);
	game->player.radius = 10;
	game->player.angle = 0;
	game->mlx = mlx_init(WIDTH, HEIGHT, "Adil's Map", true);
}

int main()
{
	t_game	game;
	init_game(&game);
	game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	draw_map(&game);
	draw_player(&game);
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return 0;
}
