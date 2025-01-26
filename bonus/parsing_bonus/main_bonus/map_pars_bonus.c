/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pars_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:40:00 by isrkik            #+#    #+#             */
/*   Updated: 2025/01/26 14:00:47 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

int	call_funcs(char **line, int i, int hold, t_pars *pars)
{
	if (last_line(line, i) == -1)
		return (-1);
	if (mofm(line, hold, pars) == -1)
		return (-1);
	if (check_mofm(pars) == -1)
		return (-1);
	return (0);
}

int	pars_map(char **line, t_pars *pars, int i)
{
	int	hold;
	int	j;

	j = 0;
	hold = i;
	while (line[i] && line[i][j] && (ft_isspace(line[i][j])
		|| line[i][j] == '1'))
		j++;
	if (!line[i] || line[i++][j] != '\n')
		return (-1);
	if (check_right(line, i) == -1)
		return (-1);
	if (check_space_first(line, &i) == -1)
		return (-1);
	if (line[i] && (line[i][0] != 1 && line[i][0] != '\n'))
		return (-1);
	else if (line[i] && line[i][0] == '\n')
	{
		if (check_below(line, i) == -1)
			return (-1);
	}
	if (call_funcs(line, i, hold, pars) == -1)
		return (-1);
	return (0);
}

void	ft_free_all(char **line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		free(line[i]);
		i++;
	}
	free(line);
}

void	helper_func(char **line)
{
	ft_free_all(line);
	ft_error("Error\n", 2);
}

void	pars_file(char **line, t_pars *pars)
{
	int	i;

	init_vars(pars, &i);
	while (line && line[i])
	{
		if (line[i] && line[i][0] == '\n')
			i++;
		if (pars_line(line[i], pars) == -1)
			helper_func(line);
		if (pars->utils.half == 6)
		{
			while (line[++i] && line[i][0] == '\n')
				;
			if (pars_map(line, pars, i) == -1)
			{
				ft_free_all(line);
				ft_error("Error\n", 2);
			}
			ft_free_all(line);
			break ;
		}
		i++;
	}
	if (!pars->map)
		ft_error("Error\n", 2);
}
