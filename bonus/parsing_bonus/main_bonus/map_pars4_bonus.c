/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pars4_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:50:12 by isrkik            #+#    #+#             */
/*   Updated: 2025/01/25 14:48:38 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

int	check_mofm_utils(t_pars *pars, int i, int *j, int *dupl)
{
	if (pars->map[i][*j] == '1')
		(*j)++;
	else if (ft_isspace(pars->map[i][*j]))
		(*j)++;
	else if (pars->map[i][*j] == '0'
		|| ft_players(pars->map[i][*j], pars) || pars->map[i][*j] == 'D')
	{
		if (check_player(pars, i, j, dupl) == -1)
			return (-1);
	}
	else if (pars->map[i][*j] == '\n')
		(*j)++;
	else
		return (-1);
	return (0);
}

int	check_mofm(t_pars *pars)
{
	int	i;
	int	j;
	int	dupl;

	i = 1;
	dupl = 0;
	while (pars->map[i])
	{
		j = 0;
		while (pars->map[i][j])
		{
			if (check_mofm_utils(pars, i, &j, &dupl) == -1)
				return (ft_free_all(pars->map), -1);
		}
		i++;
	}
	if (dupl == 0)
		return (ft_free_all(pars->map), -1);
	return (0);
}

int	count_line(char **line, int i)
{
	int	len;

	len = 0;
	while (line[i] && line[i][0] != '\n')
	{
		i++;
		len++;
	}
	return (len);
}

int	mofm(char **line, int i, t_pars *pars)
{
	int	hold;
	int	j;
	int	n;

	j = 0;
	n = 0;
	pars->len_rows = count_line(line, i);
	hold = i;
	pars->map = malloc(sizeof(char *) * (pars->len_rows + 1));
	if (!pars->map)
		return (-1);
	pars->map[pars->len_rows] = NULL;
	j = count_biggest_len(line, hold);
	pars->len_columns = j - 1;
	while (line[hold] && line[hold++][0] != '\n')
	{
		pars->map[n] = malloc(sizeof(char) * (j + 2));
		if (!pars->map[n])
			return (free_dom(pars->map, n), -1);
		pars->map[n][j] = '\0';
		pars->map[n++][j + 1] = '\0';
	}
	pars->utils.hold = i;
	cpy_map(line, j, pars);
	return (0);
}

int	check_space_first(char **line, int *i)
{
	int	j;

	while (line[*i] && (line[*i][0] == '1' || ft_isspace(line[*i][0])))
	{
		j = 0;
		while (ft_isspace(line[*i][j]))
			j++;
		if (line[*i] && line[*i][j] != '1')
			return (-1);
		(*i)++;
	}
	return (0);
}
