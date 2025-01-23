/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pars3_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:49:53 by isrkik            #+#    #+#             */
/*   Updated: 2025/01/23 16:22:19 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

void	add_to_map(char **line, t_pars *pars, int i, int length)
{
	if (line[pars->utils.hold][i] == '\n' && i == length - 1)
		pars->map[pars->utils.n][i] = '\0';
	else if (line[pars->utils.hold][i] != '\n')
		pars->map[pars->utils.n][i] = line[pars->utils.hold][i];
}

void	extra_space(t_pars *pars, int *i, int length)
{
	while (length > *i)
	{
		pars->map[pars->utils.n][*i - 1] = ' ';
		(*i)++;
	}
}

void	cpy_map(char **line, int length, t_pars *pars)
{
	int	i;
	int	len_line;

	i = 0;
	pars->utils.n = 0;
	while (line[pars->utils.hold] && line[pars->utils.hold][i] != '\n')
	{
		len_line = no_newline(line[pars->utils.hold]) + 1;
		i = 0;
		while (length > i)
		{
			if (i >= len_line && len_line < length)
			{
				extra_space(pars, &i, length);
				pars->map[pars->utils.n][i - 1] = '\0';
				break ;
			}
			else if (i < len_line)
				add_to_map(line, pars, i, length);
			i++;
		}
		i = 0;
		pars->utils.hold++;
		pars->utils.n++;
	}
}

int	ft_players(int c, t_pars *pars)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (c == 'S')
			pars->player.angle = M_PI_2;
		else if (c == 'N')
			pars->player.angle = 3 * M_PI_2;
		else if (c == 'E')
			pars->player.angle = 0;
		else if (c == 'W')
			pars->player.angle = M_PI;
		return (1);
	}
	return (0);
}

int	check_player(t_pars *pars, int i, int *j, int *dupl)
{
	if (ft_players(pars->map[i][*j], pars))
	{
		(*dupl)++;
		pars->player.y = i * TILE_SIZE + (TILE_SIZE / 2);
		pars->player.x = *j * TILE_SIZE + (TILE_SIZE / 2);
	}
	if (pars->map[i][*j] == 'D')
	{
		if (check_door(pars->map, i, *j) == -1)
			return (-1);
	}
	if (*dupl > 1 || pars->map[i - 1][*j] == ' '
		|| pars->map[i + 1][*j] == ' '
		|| pars->map[i][*j - 1] == ' '
		|| pars->map[i][*j + 1] == ' ')
		return (-1);
	(*j)++;
	return (0);
}
