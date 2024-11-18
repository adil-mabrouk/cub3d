/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_textures_pars.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:42:03 by isrkik            #+#    #+#             */
/*   Updated: 2024/11/18 23:28:26 by isrkik           ###   ########.fr       */
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

int	valid_colors(char *line, int *i, t_pars *pars, bool color)
{
	unsigned int	temp[3];
	int				b;

	b = 0;
	skip_spaces(line, i);
	while (b < 3 && line[*i])
	{
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
	pars->flag_utils.colors++;
	if (pars->flag_utils.colors == 3)
		return (-1);
	store_colors(pars, color, temp);
	pars->flag_utils.half++;
	return (0);
}

int	check_colors(char *line, int *i, t_pars *pars)
{
	if (line[*i] == 'F')
	{
		(*i)++;
		if (ft_isspace(line[*i]) && line[*i] != '\0')
			valid_colors(line, i, pars, 0);
		else
			return (-1);
	}
	else if (line[*i] == 'C')
	{
		(*i)++;
		if (ft_isspace(line[*i]) == 1 && line[*i] != '\0')
			valid_colors(line, i, pars, 1);
		else
			return (-1);
	}
	return (0);
}

int	check_directions(char *line, int i, t_pars *pars)
{
	char	temp[3];

	temp[2] = '\0';
	if (line[i] && line[i + 1])
	{
		temp[0] = line[i];
		temp[1] = line[i + 1];
	}
	if (ft_strcmp("NO", temp) == 0)
		pars->flag_utils.flag_no++;
	else if (ft_strcmp("EA", temp) == 0)
		pars->flag_utils.flag_ea++;
	else if (ft_strcmp("WE", temp) == 0)
		pars->flag_utils.flag_we++;
	else if (ft_strcmp("SO", temp) == 0)
		pars->flag_utils.flag_so++;
	if ((ft_strcmp("NO", temp) != 0 && ft_strcmp("SO", temp) != 0
			&& ft_strcmp("EA", temp) != 0 && ft_strcmp("WE", temp) != 0)
		|| (pars->flag_utils.flag_no >= 2 || pars->flag_utils.flag_ea >= 2
			|| pars->flag_utils.flag_we >= 2 || pars->flag_utils.flag_so >= 2))
		return (-1);
	if (line[i] == '\0')
		return (-1);
	return (0);
}

int	pars_line(char *line, t_pars *pars)
{
	int		i;

	i = 0;
	skip_spaces(line, &i);
	if (line[i] == '\0')
		return (0);
	if (check_colors(line, &i, pars) == -1)
		return (-1);
	if (line[i] == '\n')
		return (0);
	if (line[i] != 'C' && line[i] != 'F')
	{
		if (check_directions(line, i, pars) == -1)
			return (-1);
		skip_spaces(line, &i);
		if (line[i] == '\0')
			return (-1);
		pars->flag_utils.half++;
	}
	return (0);
}
