/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_tex_colors3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:30:20 by isrkik            #+#    #+#             */
/*   Updated: 2025/01/26 17:26:06 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_colors(char *line, int *i, t_pars *pars)
{
	if (line[*i] == 'F')
	{
		pars->utils.f_color++;
		(*i)++;
		if (ft_isspace(line[*i]) && line[*i] != '\0')
		{
			if (valid_colors(line, i, pars, 0) == -1)
				return (-1);
		}
		else
			return (-1);
	}
	else if (line[*i] == 'C')
	{
		pars->utils.c_color++;
		(*i)++;
		if (ft_isspace(line[*i]) == 1 && line[*i] != '\0')
		{
			if (valid_colors(line, i, pars, 1) == -1)
				return (-1);
		}
		else
			return (-1);
	}
	return (0);
}

int	space_error(char *line, int b)
{
	while (line[b] && ft_isspace(line[b]))
	{
		b++;
		if (ft_isspace(line[b]) == 0 && line[b] != '\n')
			return (-1);
	}
	return (0);
}
