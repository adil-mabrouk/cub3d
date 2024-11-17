/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_part.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: i61mail <i61mail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:40:00 by isrkik            #+#    #+#             */
/*   Updated: 2024/11/17 19:37:02 by i61mail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void valid_colors(char *line, int *i, t_pars *pars)
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
	pars->flag_utils.half++;
}

void	check_colors(char *line, int *i, t_pars *pars)
{
	if (line[*i] == 'F')
	{
		(*i)++;
		if (ft_isspace(line[*i]) && line[*i] != '\0')
			valid_colors(line, i, pars);
		else
			ft_error("invalid colors\n", 2);
	}
	else if (line[*i] == 'C')
	{
		(*i)++;
		if (ft_isspace(line[*i]) == 1 && line[*i] != '\0')
			valid_colors(line, i, pars);
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


void	mofm(char **line, int i)
{
	char	**temp;
	int	len = 0;
	int	hold;
	int j;

	j = 0;
	hold = i;
	while (line[i] && line[i][0] != '\n')
	{
		i++;
		len++;		
	}
	i = hold;
	temp = malloc(sizeof(char *) * (len + 1));
	if (!temp)
		return ;
	temp[len] = NULL;
	j = count_biggest_len(line, hold);
	int k = j;
	int n = 0;
	while (line[hold] && line[hold][0] != '\n')
	{
		temp[n] = malloc(sizeof(char) * (j + 1));
		hold++;
		n++;
	}
	exit(EXIT_SUCCESS);
}

void	pars_map(char **line, t_pars *pars, int i)
{
	int	hold;
	int	j;
	int	k;

	j = 0;
	hold = i;
	k = i;
	(void)pars;
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
	mofm(line, hold);
	exit(EXIT_SUCCESS);
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
			while (line[++i] && line[i][0] == '\n') ;
			pars_map(line, pars, i);
		}
		i++;
	}
	
}
