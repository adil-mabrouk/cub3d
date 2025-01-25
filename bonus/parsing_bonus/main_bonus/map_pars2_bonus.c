/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pars2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:49:36 by isrkik            #+#    #+#             */
/*   Updated: 2025/01/25 14:47:03 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

int	check_below(char **line, int i)
{
	int	hold;
	int	j;

	j = 0;
	hold = i - 1;
	while (line[hold] && line[hold][j]
		&& (ft_isspace(line[hold][j]) || line[i][j] == '1'))
		j++;
	if (line[i][j] != '\n')
		return (-1);
	while (line[i] && line[i][0] == '\n')
		i++;
	if (line[i] && line[i][0] != '\0')
		return (-1);
	return (0);
}

int	last_line(char **line, int i)
{
	int	j;

	j = 0;
	i--;
	while (line[i] && line[i][j]
		&& (ft_isspace(line[i][j]) || line[i][j] == '1'))
		j++;
	if (line[i][j] != '\0' && line[i][j] != '\n')
		return (-1);
	return (0);
}

int	check_right(char **line, int i)
{
	int	j;

	while (line[i])
	{
		j = ft_strnewline(line[i]);
		if (j != 0 && line[i][j - 1] && (line[i][j - 1] != '1'
			&& line[i][j - 1] != '\n' && line[i][j - 1] != ' '))
			return (-1);
		i++;
	}
	return (0);
}

int	count_biggest_len(char **line, int i)
{
	int	j;
	int	b;

	j = 0;
	b = 0;
	while (line[i] && line[i][0] != '\n')
	{
		if (!line[i + 1])
		{
			while (line[i][b] && line[i][b] != '\n')
				b++;
			if (line[i][b] == '\0' && ft_strlen(line[i]) > j)
				j = ft_strlen(line[i]) + 1;
		}
		if (ft_strlen(line[i]) > j)
			j = ft_strlen(line[i]);
		i++;
	}
	return (j);
}

int	no_newline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}
