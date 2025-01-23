/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_tex_colors2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:49:12 by isrkik            #+#    #+#             */
/*   Updated: 2025/01/23 13:21:04 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	create_rgb(int r, int g, int b)
{
	int	col;

	col = r << 16 | g << 8 | b;
	return (col);
}

void	store_colors(t_pars *pars, int color, unsigned int *temp)
{
	if (color == 0)
		pars->f_color = create_rgb(temp[0], temp[1], temp[2]);
	else
		pars->c_color = create_rgb(temp[0], temp[1], temp[2]);
}

int	skip_space_color(char *line, int *i)
{
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\n'))
	{
		(*i)++;
		if (line[*i] == '\n')
			return (-1);
	}
	return (0);
}

int	check_rgb(t_pars *pars, bool color, unsigned int *temp)
{
	pars->utils.colors++;
	if (pars->utils.colors == 3)
		return (-1);
	store_colors(pars, color, temp);
	pars->utils.half++;
	return (0);
}

int	valid_colors(char *line, int *i, t_pars *pars, bool color)
{
	unsigned int	temp[3];
	int				b;

	b = 0;
	skip_spaces(line, i);
	while (b < 3 && line[*i])
	{
		if (skip_space_color(line, i) == -1)
			return (-1);
		temp[b] = ft_atoi(&line[*i]);
		if (temp[b] > 255)
			return (-1);
		while (line[*i] && (line[*i] >= '0' || line[*i] == ' ')
			&& line[*i] != '\n')
			(*i)++;
		if (line[*i] == ',')
			(*i)++;
		b++;
	}
	if (line[*i] == '\0')
		return (-1);
	if (check_rgb(pars, color, temp) == -1)
		return (-1);
	return (0);
}
