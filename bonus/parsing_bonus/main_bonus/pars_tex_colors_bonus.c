/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_tex_colors_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:42:03 by isrkik            #+#    #+#             */
/*   Updated: 2025/01/23 16:09:06 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

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

void	check_textures_helper(t_pars *pars, char *temp, int b, char *line)
{
	int	fd;

	if (ft_strcmp("WE", temp) == 0)
	{
		pars->west = ft_substr(line, pars->utils.first_i,
				b - pars->utils.first_i);
		fd = open(pars->north, O_RDONLY);
		if (fd < 0)
			ft_error("invalid texture3\n", 2);
		pars->utils.flag_we++;
	}
	else if (ft_strcmp("SO", temp) == 0)
	{
		pars->south = ft_substr(line, pars->utils.first_i,
				b - pars->utils.first_i);
		fd = open(pars->north, O_RDONLY);
		if (fd < 0)
			ft_error("invalid texture4\n", 2);
		pars->utils.flag_so++;
	}
}

void	check_textures(t_pars *pars, char *temp, int b, char *line)
{
	int	fd;

	pars->utils.first_i = b;
	while (line[b] && !ft_isspace(line[b]) && line[b] != '\n')
		b++;
	if (ft_strcmp("NO", temp) == 0)
	{
		pars->north = ft_substr(line, pars->utils.first_i,
				b - pars->utils.first_i);
		fd = open(pars->north, O_RDONLY);
		if (fd < 0)
			ft_error("invalid texture1\n", 2);
		pars->utils.flag_no++;
	}
	else if (ft_strcmp("EA", temp) == 0)
	{
		pars->east = ft_substr(line, pars->utils.first_i,
				b - pars->utils.first_i);
		fd = open(pars->north, O_RDONLY);
		if (fd < 0)
			ft_error("invalid texture2\n", 2);
		pars->utils.flag_ea++;
	}
	check_textures_helper(pars, temp, b, line);
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
	check_textures(pars, temp, b, line);
	if ((ft_strcmp("NO", temp) != 0 && ft_strcmp("SO", temp) != 0
			&& ft_strcmp("EA", temp) != 0 && ft_strcmp("WE", temp) != 0)
		|| (pars->utils.flag_no >= 2 || pars->utils.flag_ea >= 2
			|| pars->utils.flag_we >= 2 || pars->utils.flag_so >= 2))
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
