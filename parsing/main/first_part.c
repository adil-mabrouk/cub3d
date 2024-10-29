/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_part.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:40:00 by isrkik            #+#    #+#             */
/*   Updated: 2024/10/29 12:26:09 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void valid_colors(char *line, int *i)
{
	unsigned int temp[3];
	int b;

	b = 0;
	skip_spaces(line, i);
	while (b < 3 && line[*i])
	{
		temp[b] = ft_atoi(&line[*i]);
		if (temp[b] > 255)
			ft_error("Color out of range\n", 2);
		while (line[*i] && line[*i] >= '0' && line[*i] != '\n')
			(*i)++;
		if (line[*i] == ',')
			(*i)++;
		b++;
	}
	if (line[*i] == '\0')
		ft_error("incomplete map file\n", 2);
}

void	check_colors(char *line, int *i)
{
	if (line[*i] == 'F')
	{
		(*i)++;
		if (ft_isspace(line[*i]) && line[*i] != '\0')
			valid_colors(line, i);
		else
			ft_error("invalid colors\n", 2);
	}
	else if (line[*i] == 'C')
	{
		(*i)++;
		if (ft_isspace(line[*i]) == 1 && line[*i] != '\0')
			valid_colors(line, i);
		else
			ft_error("invalid colors\n", 2);
	}
}

void	pars_line(char *line, t_pars *pars)
{
	int		i;
	char	temp[3];
	
	i = 0;
	temp[2] = '\0';
	skip_spaces(line, &i);
	if (line[i] == '\0')
		return ;
	check_colors(line, &i);
	if (line[i] == '\n')
		return ;
	if (line[i] != 'C' && line[i] != 'F')
	{
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
			&& ft_strcmp("EA", temp) != 0 && ft_strcmp("WE", temp) != 0) || (pars->flag_utils.flag_no >= 2 \
				|| pars->flag_utils.flag_ea >= 2 || pars->flag_utils.flag_we >= 2 || pars->flag_utils.flag_so >= 2))
			ft_error("invalid direction\n", 2);
		if (line[i] == '\0')
			ft_error("invalid direction\n", 2);
		skip_spaces(line, &i);
		if (line[i] == '\0')
			ft_error("invalid direction\n", 2);
	}
}

void	pars_file(char **line, t_pars *pars)
{
	int	i;

	i = 0;
	pars->flag_utils.flag_ea = 0;
	pars->flag_utils.flag_we = 0;
	pars->flag_utils.flag_no = 0;
	pars->flag_utils.flag_so = 0;
	while (line && line[i])
	{
		if (line[i][0] == '\n')
			i++;
		pars_line(line[i], pars);
		i++;
	}
}
