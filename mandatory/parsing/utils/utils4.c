/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:28:31 by isrkik            #+#    #+#             */
/*   Updated: 2025/01/26 13:27:25 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

size_t	ft_strnewlen(char *str)
{
	size_t	n;

	n = 0;
	while (*str != '\n')
	{
		n++;
		str++;
	}
	return (n);
}

void	skip_spaces(char *line, int *i)
{
	if (!line)
		return ;
	while (line[*i])
	{
		if (ft_isspace(line[*i]))
			(*i)++;
		else
			break ;
	}
}

int	ft_strnewline(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}
