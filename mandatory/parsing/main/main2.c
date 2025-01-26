/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:32:03 by isrkik            #+#    #+#             */
/*   Updated: 2025/01/26 17:22:47 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	read_file(int fd2, int len, char ***line)
{
	int		i;
	char	*temp;

	temp = NULL;
	i = 0;
	while (i < len)
	{
		temp = get_next_line(fd2);
		if (temp == NULL)
			break ;
		(*line)[i] = ft_strdup(temp);
		if (!(*line)[i])
			ft_error("allocation failed\n", 2);
		free(temp);
		i++;
	}
}

void	open_file(char *av, int *fd, int *fd2)
{
	*fd = open(av, O_RDWR);
	if (*fd < 0)
		ft_error("open error\n", 2);
	*fd2 = open(av, O_RDWR);
	if (*fd2 < 0)
	{
		close(*fd);
		ft_error("open error\n", 2);
	}
}

void	init_vars(t_pars *pars, int *i)
{
	pars->utils.f_color = 0;
	pars->utils.c_color = 0;
	pars->utils.flag_ea = 0;
	pars->utils.flag_we = 0;
	pars->utils.flag_no = 0;
	pars->utils.flag_so = 0;
	pars->utils.colors = 0;
	pars->utils.half = 0;
	pars->map = NULL;
	*i = 0;
}

void	free_dom(char **s, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(s[i]);
		i++;
	}
	free(s);
}
