/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:30:56 by isrkik            #+#    #+#             */
/*   Updated: 2024/10/28 19:49:03 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	parse_name(char *av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	if (av[i - 1] == 'b')
	{
		if (av[--i - 1] == 'u')
		{
			if (av[--i - 1] == 'c')
			{
				if (av[--i - 1] == '.')
				{
					if (i - 1 != 0)
						return (1);
				}
			}
		}
	}
	else
		return (-1);
	return (0);
}

void	copy_to_2d(int len, char ***line, int fd2)
{
	char	*temp;
	int		i;

	i = 0;
	temp = NULL;
	if (len > 0)
	{
		*line = malloc(sizeof(char *) * (len + 1));
		if (!*line)
			return ;
		(*line)[len] = NULL;
	}
	while(i < len)
	{
		temp = get_next_line(fd2);
		if (temp == NULL)
			break ;
		(*line)[i] = ft_strdup(temp);
		free(temp);
		// printf("%s", (*line)[i]);
		i++;
	}
	close(fd2);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v')
		return (1);
	return (0);
}

void	skip_spaces(char *line, int *i)
{
	while (line[*i])
	{
		if (ft_isspace(line[*i]))
			(*i)++;
		else
			break ;
	}
}

// void	store_direction(char *temp, char *line, int i, t_pars *pars)
// {
// 	int	start;

// 	start = i;
// 	if (ft_strcmp(temp, "NO") == 0)
// 	{
// 		while (line[i])
// 			i++;
// 		pars->north = ft_substr(line, start, i - start);
// 	}
// }

void	valid_colors(char *line, int *i)
{
	char	temp[4];
	int	b;

	temp[0] = '\0';
	temp[1] = '\0';
	temp[2] = '\0';
	temp[3] = '\0';
	skip_spaces(line, i);
	while (line[*i])
	{
		b = 0;
		while (line[*i] != ',' && line[*i] != '\n')
		{
			temp[b] = line[*i];
			b++;
			(*i)++;
		}
		if (ft_strcmp(temp, "255") > 0)
			ft_error("colors out of range\n", 2);
		(*i)++;
	}
}

void	check_colors(char *line, int *i)
{
	if (line[*i] == 'F')
	{
		(*i)++;
		if (ft_isspace(line[*i]) == 1 && line[*i] != '\0')
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
	
	(void)pars;
	i = 0;
	temp[2] = '\0';
	skip_spaces(line, &i);
	if (line[i] == '\0')
		return ;
	check_colors(line, &i);
	if (line[i] && line[i + 1])
	{
		temp[0] = line[i];
		temp[1] = line[i + 1];
	}
	if (ft_strcmp("NO", temp) != 0 && ft_strcmp("SO", temp) != 0
		&& ft_strcmp("EA", temp) != 0 && ft_strcmp("WE", temp) != 0)
		ft_error("invalid direction\n", 2);
	if (line[i] == '\0')
		ft_error("invalid direction\n", 2);
	skip_spaces(line, &i);
	if (line[i] == '\0')
		ft_error("invalid direction\n", 2);
}

void	pars_file(char **line, t_pars *pars)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i][0] == '\n')
			i++;
		pars_line(line[i], pars);
		i++;
	}
}

int	first_half(char *av, t_pars	*pars)
{
	char	*temp;
	char	**line;
	int		fd;
	int		fd2;
	int		len;

	len = 0;
	fd = open(av, O_RDWR);
	if (fd < 0)
		ft_error("open error\n", 2);
	fd2 = open(av, O_RDWR);
	if (fd2 < 0)
		ft_error("open error\n", 2);
	line = NULL;
	temp = NULL;
	while (1)
	{
		temp = get_next_line(fd);
		if (temp == NULL)
			break ;
		free(temp);
		len++;
	}
	close(fd);
	copy_to_2d(len, &line, fd2);
	pars_file(line, pars);
	return (0);
}

int main(int ac, char **av)
{
	t_pars	pars;

	if (ac == 2)
	{
		if (parse_name(av[1]) == 1)
		{
			if (first_half(av[1], &pars) == -1)
				ft_error("malloc error\n", 2);
			return (0);
		}
		else
			ft_error("Name error\n", 2);
	}
	else
		ft_error("not enough args\n", 2);
	return (0);
}
