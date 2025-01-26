/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:30:56 by isrkik            #+#    #+#             */
/*   Updated: 2025/01/26 15:55:59 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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
	if (len > 0)
	{
		*line = malloc(sizeof(char *) * (len + 1));
		if (!*line)
		{
			close(fd2);
			ft_error("allocation failed\n", 2);
		}
		(*line)[len] = NULL;
	}
	read_file(fd2, len, line);
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

	open_file(av, &fd, &fd2);
	len = 0;
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
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	mlx_loop_hook(game->mlx, loop_hook, game);
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
