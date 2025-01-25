/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_tex_colors3_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:42:55 by isrkik            #+#    #+#             */
/*   Updated: 2025/01/25 14:44:12 by isrkik           ###   ########.fr       */
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
