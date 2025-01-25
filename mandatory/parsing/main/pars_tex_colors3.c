/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_tex_colors3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:30:20 by isrkik            #+#    #+#             */
/*   Updated: 2025/01/25 14:31:18 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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
