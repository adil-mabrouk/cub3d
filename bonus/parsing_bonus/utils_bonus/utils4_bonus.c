/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:44:23 by isrkik            #+#    #+#             */
/*   Updated: 2025/01/23 16:22:48 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

size_t	ft_strnewlen(char *str)
{
	size_t	n;

	n = 0;
	while (*str != '\n')
	{
		n++;
		str++;
	}
	return (n);
}

void	skip_spaces(char *line, int *i)
{
	while (line[*i])
	{
		if (ft_isspace(line[*i]))
			(*i)++;
		else
			break ;
	}
}

int	ft_strnewline(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

int	check_door(char **map, int i, int j)
{
	if (map[i - 1][j] == '1' && map[i + 1][j] == '1')
		return (0);
	else if (map[i][j - 1] == '1' && map[i][j + 1] == '1')
		return (0);
	else
		return (-1);
}
