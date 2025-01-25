/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_tex_colors_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:42:03 by isrkik            #+#    #+#             */
/*   Updated: 2025/01/25 14:56:28 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

int	check_textures_helper2(t_pars *pars, char *temp, int b, char *line)
{
	if (ft_strcmp("WE", temp) == 0)
	{
		pars->utils.flag_we++;
		if (pars->utils.flag_we >= 2)
			return (-1);
		pars->west = ft_substr(line, pars->utils.first_i,
				b - pars->utils.first_i);
		pars->utils.fd = open(pars->west, O_RDONLY);
		if (pars->utils.fd < 0)
			return (free(pars->west), -1);
	}
	else if (ft_strcmp("SO", temp) == 0)
	{
		pars->utils.flag_so++;
		if (pars->utils.flag_so >= 2)
			return (-1);
		pars->south = ft_substr(line, pars->utils.first_i,
				b - pars->utils.first_i);
		pars->utils.fd = open(pars->south, O_RDONLY);
		if (pars->utils.fd < 0)
			return (free(pars->south), -1);
	}
	close(pars->utils.fd);
	return (0);
}

int	check_textures_helper(t_pars *pars, char *temp, int b, char *line)
{
	if (ft_strcmp("EA", temp) == 0)
	{
		pars->utils.flag_ea++;
		if (pars->utils.flag_ea >= 2)
			return (-1);
		pars->east = ft_substr(line, pars->utils.first_i,
				b - pars->utils.first_i);
		pars->utils.fd = open(pars->east, O_RDONLY);
		if (pars->utils.fd < 0)
			return (free(pars->east), -1);
	}
	close(pars->utils.fd);
	if (check_textures_helper2(pars, temp, b, line) == -1)
		return (-1);
	return (0);
}

int	check_textures(t_pars *pars, char *temp, int b, char *line)
{
	pars->utils.fd = -1;
	pars->utils.first_i = b;
	while (line[b] && !ft_isspace(line[b]) && line[b] != '\n')
		b++;
	if (ft_strcmp("NO", temp) == 0)
	{
		pars->utils.flag_no++;
		if (pars->utils.flag_no >= 2)
			return (-1);
		pars->north = ft_substr(line, pars->utils.first_i,
				b - pars->utils.first_i);
		pars->utils.fd = open(pars->north, O_RDONLY);
		if (pars->utils.fd < 0)
			return (free(pars->north), -1);
		close(pars->utils.fd);
	}
	if (check_textures_helper(pars, temp, b, line) == -1)
		return (-1);
	return (0);
}

int	check_directions(char *line, int i, t_pars *pars)
{
	char	temp[3];
	int		b;

	temp[2] = '\0';
	if (line[i] && line[i + 1])
	{
		temp[0] = line[i];
		temp[1] = line[i + 1];
	}
	b = i + 2;
	while (line[b] && ft_isspace(line[b]))
		b++;
	if (check_textures(pars, temp, b, line) == -1)
		return (-1);
	if ((ft_strcmp("NO", temp) != 0 && ft_strcmp("SO", temp) != 0
			&& ft_strcmp("EA", temp) != 0 && ft_strcmp("WE", temp) != 0))
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
		pars->utils.half++;
	}
	return (0);
}
