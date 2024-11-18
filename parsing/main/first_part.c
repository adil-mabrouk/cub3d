/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_part.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:40:00 by isrkik            #+#    #+#             */
/*   Updated: 2024/11/18 16:34:24 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	create_rgb(int r, int g, int b)
{
	int	col;

	col = r << 16 | g << 8 | b;
	return (col);
}

void valid_colors(char *line, int *i, t_pars *pars, bool color)
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
		while (line[*i] && (line[*i] >= '0' || line[*i] == ' ') && line[*i] != '\n')
			(*i)++;
		if (line[*i] == ',')
			(*i)++;
		b++;
	}
	if (line[*i] == '\0')
		ft_error("incomplete map file\n", 2);
	pars->flag_utils.colors++;
	if (pars->flag_utils.colors == 3)
		ft_error("duplicate colors\n", 2);
	if (color == 0)
		pars->f_color = create_rgb(temp[0], temp[1], temp[2]);
	else
		pars->c_color = create_rgb(temp[0], temp[1], temp[2]);
	pars->flag_utils.half++;
}

void	check_colors(char *line, int *i, t_pars *pars)
{
	if (line[*i] == 'F')
	{
		(*i)++;
		if (ft_isspace(line[*i]) && line[*i] != '\0')
			valid_colors(line, i, pars, 0);
		else
			ft_error("invalid colors\n", 2);
	}
	else if (line[*i] == 'C')
	{
		(*i)++;
		if (ft_isspace(line[*i]) == 1 && line[*i] != '\0')
			valid_colors(line, i, pars, 1);
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
	check_colors(line, &i, pars);
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
		pars->flag_utils.half++;
	}
}

void	check_below(char **line, int i)
{
	int	hold;
	int	j;

	j = 0;
	hold = i - 1;
	while (line[hold] && line[hold][j] && (ft_isspace(line[hold][j]) || line[i][j] == '1'))
		j++;
	if (line[i][j] != '\n')
		ft_error("unclosed map4\n", 2);
	while (line[i] && line[i][0] == '\n')
		i++;
	if (line[i] && line[i][0] != '\0')
		ft_error("map error\n", 2);
}

void	last_line(char **line, int i)
{
	int	j;

	j = 0;
	i--;
	while (line[i] && line[i][j] && (ft_isspace(line[i][j]) || line[i][j] == '1'))
		j++;
	if (line[i][j] != '\0' && line[i][j] != '\n')
		ft_error("unclosed map10\n", 2);
}

void	check_right(char **line, int i)
{
	int	j;

	while (line[i])
	{
		j = ft_strnewline(line[i]);
		if (j != 0 && line[i][j - 1] && (line[i][j - 1] != '1' && line[i][j - 1] != '\n' && line[i][j - 1] != ' '))
			ft_error("unclosed map6\n", 2);
		i++;
	}
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
					pars->temp[n][i - 1] = ' ';
					i++;
				}
				pars->temp[n][i - 1] = '\n';
				break ;
			}
			else if (i < len_line)
			{
				if (line[hold][i] == '\n' && i == length - 1)
					pars->temp[n][i] = line[hold][i];
				else if (line[hold][i] != '\n')
					pars->temp[n][i] = line[hold][i];
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

void	check_mofm(t_pars *pars)
{
	int	i;
	int	j;
	int	dupl;

	i = 1;
	dupl = 0;
	while (pars->temp[i])
	{
		j = 0;
		while (pars->temp[i][j])
		{
			if (pars->temp[i][j] == '1')
				j++;
			else if (ft_isspace(pars->temp[i][j]))
				j++;
			else if (pars->temp[i][j] == '0' || ft_players(pars->temp[i][j]))
			{
				if (ft_players(pars->temp[i][j]))
					dupl++;
				if (dupl > 1)
					ft_error("duplicate players\n", 2);
				if (pars->temp[i - 1][j] == ' ' || pars->temp[i + 1][j] == ' '
					|| pars->temp[i][j - 1] == ' ' || pars->temp[i][j + 1] == ' ')
					ft_error("space between 0s\n", 2);
				j++;
			}
			else if (pars->temp[i][j] == '\n')
				j++;
			else
				ft_error("invalid char\n", 2);
		}
		i++;
	}
}

void	mofm(char **line, int i, t_pars *pars)
{
	int	len = 0;
	int	hold;
	int j;
	int n = 0;

	j = 0;
	hold = i;
	pars->temp = NULL;
	while (line[hold] && line[hold][0] != '\n')
	{
		hold++;
		len++;		
	}
	hold = i;
	pars->temp = malloc(sizeof(char *) * (len + 1));
	if (!pars->temp)
		return ;
	pars->temp[len] = NULL;
	j = count_biggest_len(line, hold);
	while (line[hold] && line[hold][0] != '\n')
	{
		pars->temp[n] = malloc(sizeof(char) * (j + 2));
		pars->temp[n][j] = '\0';
		pars->temp[n][j + 1] = '\0';
		hold++;
		n++;
	}
	cpy_map(line, i, j, pars);
	check_mofm(pars);
}

void	pars_map(char **line, t_pars *pars, int i)
{
	int	hold;
	int	j;
	int	k;

	j = 0;
	hold = i;
	k = i;
	while (line[i] && line[i][j] && (ft_isspace(line[i][j]) || line[i][j] == '1'))//kantchecki biha line lowl
		j++;
	if (line[i++][j] != '\n')
		ft_error("unclosed map\n", 2);
	check_right(line, i);//kanchecki biha akhir char f kola line
	while (line[i] && (line[i][0] == '1' || ft_isspace(line[i][0]))) // kanchecki biha awal char f kola line
	{
		j = 0;
		while (ft_isspace(line[i][j]))
			j++;
		if (line[i] && line[i][j] != '1')
			ft_error("unclosed map2\n", 2);
		i++;
	}
	if (line[i] && (line[i][0] != 1 && line[i][0] != '\n'))
		ft_error("unclosed map3\n", 2);
	else if (line[i] && line[i][0] == '\n')
		check_below(line, i);//kenchecki biha akhir char f akhir line
	last_line(line, i);//kanchecki biha akhir line
	mofm(line, hold, pars);
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
	while (line && line[i])
	{
		if (line[i] && line[i][0] == '\n')
			i++;
		pars_line(line[i], pars);
		if (pars->flag_utils.half == 6)
		{
			while (line[++i] && line[i][0] == '\n');
			pars_map(line, pars, i);
			break ;
		}
		i++;
	}
	
}
