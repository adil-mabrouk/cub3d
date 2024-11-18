/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:30:56 by isrkik            #+#    #+#             */
/*   Updated: 2024/11/18 16:35:05 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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
		i++;
	}
	close(fd2);
}

int	first_half(char *av, t_pars	*pars)
{
	char	*temp;
	char	**line;
	int		fd;
	int		fd2;
	int		len;

	(void)pars;
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
	printf("%d\n", pars->c_color);
	printf("%d\n", pars->f_color);
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
