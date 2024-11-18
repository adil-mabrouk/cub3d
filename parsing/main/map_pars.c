/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:40:00 by isrkik            #+#    #+#             */
/*   Updated: 2024/11/18 23:38:51 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_below(char **line, int i)
{
	int	hold;
	int	j;

	j = 0;
	hold = i - 1;
	while (line[hold] && line[hold][j]
		&& (ft_isspace(line[hold][j]) || line[i][j] == '1'))
		j++;
	if (line[i][j] != '\n')
		return (-1);
	while (line[i] && line[i][0] == '\n')
		i++;
	if (line[i] && line[i][0] != '\0')
		return (-1);
	return (0);
}

int	last_line(char **line, int i)
{
	int	j;

	j = 0;
	i--;
	while (line[i] && line[i][j]
		&& (ft_isspace(line[i][j]) || line[i][j] == '1'))
		j++;
	if (line[i][j] != '\0' && line[i][j] != '\n')
		return (-1);
	return (0);
}

int	check_right(char **line, int i)
{
	int	j;

	while (line[i])
	{
		j = ft_strnewline(line[i]);
		if (j != 0 && line[i][j - 1] && (line[i][j - 1] != '1'
			&& line[i][j - 1] != '\n' && line[i][j - 1] != ' '))
			return (-1);
		i++;
	}
	return (0);
}

int	count_biggest_len(char **line, int i)
{
	int	j;

	j = 0;
	while (line[i] && line[i][0] != '\n')
	{
		if (ft_strlen(line[i]) > j)
			j = ft_strlen(line[i]);
		i++;
	}
	return (j);
}

void	cpy_map(char **line, int hold, int length, t_pars *pars)
{
	int	n;
	int	i;
	int	len_line;

	i = 0;
	n = 0;
	while (line[hold] && line[hold][i] != '\n')
	{
		len_line = ft_strlen(line[hold]);
		i = 0;
		while (length > i)
		{
			if (i >= len_line && len_line < length)
			{
				while (length > i)
				{
					pars->map[n][i - 1] = ' ';
					i++;
				}
				pars->map[n][i - 1] = '\n';
				break ;
			}
			else if (i < len_line)
			{
				if (line[hold][i] == '\n' && i == length - 1)
					pars->map[n][i] = line[hold][i];
				else if (line[hold][i] != '\n')
					pars->map[n][i] = line[hold][i];
			}
			i++;
		}
		i = 0;
		hold++;
		n++;
	}
}

int	ft_players(int c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
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
			if (pars->map[i][j] == '1')
				j++;
			else if (ft_isspace(pars->map[i][j]))
				j++;
			else if (pars->map[i][j] == '0' || ft_players(pars->map[i][j]))
			{
				if (ft_players(pars->map[i][j]))
					dupl++;
				if (dupl > 1)
					return (-1);
				if (pars->map[i - 1][j] == ' ' || pars->map[i + 1][j] == ' '
					|| pars->map[i][j - 1] == ' '
					|| pars->map[i][j + 1] == ' ')
					return (-1);
				j++;
			}
			else if (pars->map[i][j] == '\n')
				j++;
			else
				return (-1);
		}
		i++;
	}
	return (0);
}

int	mofm(char **line, int i, t_pars *pars)
{
	int	len;
	int	hold;
	int	j;
	int	n;

	j = 0;
	n = 0;
	len = 0;
	hold = i;
	while (line[hold] && line[hold][0] != '\n')
	{
		hold++;
		len++;
	}
	pars->len_columns = len;
	hold = i;
	pars->map = malloc(sizeof(char *) * (len + 1));
	if (!pars->map)
		return (-1);
	pars->map[len] = NULL;
	j = count_biggest_len(line, hold);
	pars->len_rows = j;
	while (line[hold] && line[hold][0] != '\n')
	{
		pars->map[n] = malloc(sizeof(char) * (j + 2));
		if (!pars->map[n])
			return (-1);
		pars->map[n][j] = '\0';
		pars->map[n][j + 1] = '\0';
		hold++;
		n++;
	}
	cpy_map(line, i, j, pars);
	if (check_mofm(pars) == -1)
		return (-1);
	return (0);
}

int		pars_map(char **line, t_pars *pars, int i)
{
	int	hold;
	int	j;
	int	k;

	j = 0;
	hold = i;
	k = i;
	while (line[i] && line[i][j] && (ft_isspace(line[i][j])
		|| line[i][j] == '1'))
		j++;
	if (line[i++][j] != '\n')
		return (-1);
	if (check_right(line, i) == -1)
		return (-1);
	while (line[i] && (line[i][0] == '1' || ft_isspace(line[i][0])))
	{
		j = 0;
		while (ft_isspace(line[i][j]))
			j++;
		if (line[i] && line[i][j] != '1')
			return (-1);
		i++;
	}
	if (line[i] && (line[i][0] != 1 && line[i][0] != '\n'))
		return (-1);
	else if (line[i] && line[i][0] == '\n')
	{
		if (check_below(line, i) == -1)
			return (-1);
	}
	if (last_line(line, i) == -1)
		return (-1);
	if (mofm(line, hold, pars) == -1)
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

void	pars_file(char **line, t_pars *pars)
{
	int	i;

	i = 0;
	pars->flag_utils.flag_ea = 0;
	pars->flag_utils.flag_we = 0;
	pars->flag_utils.flag_no = 0;
	pars->flag_utils.flag_so = 0;
	pars->flag_utils.colors = 0;
	pars->flag_utils.half = 0;
	pars->map = NULL;
	while (line && line[i])
	{
		if (line[i] && line[i][0] == '\n')
			i++;
		if (pars_line(line[i], pars) == -1)
		{
			ft_error("Error\n", 2);
			ft_free_all(line);
			break ;
		}
		if (pars->flag_utils.half == 6)
		{
			while (line[++i] && line[i][0] == '\n')
				;
			if (pars_map(line, pars, i) == -1)
				ft_error("Error\n", 2);
			ft_free_all(line);
			break ;
		}
		i++;
	}
}
