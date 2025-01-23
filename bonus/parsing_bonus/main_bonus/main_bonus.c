/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:30:56 by isrkik            #+#    #+#             */
/*   Updated: 2025/01/23 22:32:33 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

int	parse_name(char *av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	if (av[i - 1] == 'b')
	{
		if (av[--i - 1] == 'u')
		{
			if (av[--i - 1] == 'c')
			{
				if (av[--i - 1] == '.')
				{
					if (i - 1 != 0)
						return (1);
				}
			}
		}
	}
	else
		return (-1);
	return (0);
}

void	copy_to_2d(int len, char ***line, int fd2, t_pars *pars)
{
	char	*temp;
	int		i;

	i = 0;
	temp = NULL;
	if (len > 0)
	{
		*line = malloc(sizeof(char *) * (len + 1));
		if (!*line)
			return ;
		(*line)[len] = NULL;
	}
	while (i < len)
	{
		temp = get_next_line(fd2);
		if (temp == NULL)
			break ;
		(*line)[i] = ft_strdup(temp);
		free(temp);
		i++;
	}
	close(fd2);
	pars_file(*line, pars);
}

int	first_half(char *av, t_pars	*pars)
{
	char	*temp;
	char	**line;
	int		fd;
	int		fd2;
	int		len;

	len = 0;
	fd = open(av, O_RDWR);
	if (fd < 0)
		ft_error("open error\n", 2);
	fd2 = open(av, O_RDWR);
	if (fd2 < 0)
		ft_error("open error\n", 2);
	line = NULL;
	temp = NULL;
	while (1)
	{
		temp = get_next_line(fd);
		if (temp == NULL)
			break ;
		free(temp);
		len++;
	}
	close(fd);
	return (copy_to_2d(len, &line, fd2, pars), 0);
}

void	ft_execute(t_game *game, t_pars *pars)
{
	game->pars = pars;
	init_game(game);
	ft_raycast(game);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	mlx_image_to_window(game->mlx, game->mini_map, 10, 10);
	mlx_loop_hook(game->mlx, loop_hook, game);
	mlx_key_hook(game->mlx, &key_handler, game);
	mlx_cursor_hook(game->mlx, mouse_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}

int	main(int ac, char **av)
{
	t_pars	pars;
	t_game	game;

	if (ac == 2)
	{
		if (parse_name(av[1]) == 1)
		{
			if (first_half(av[1], &pars) == -1)
				ft_error("malloc error\n", 2);
			else
				ft_execute(&game, &pars);
			return (0);
		}
		else
			ft_error("Name error\n", 2);
	}
	else
		ft_error("not enough args\n", 2);
	return (0);
}
