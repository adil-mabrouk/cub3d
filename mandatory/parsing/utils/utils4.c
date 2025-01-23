/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:28:31 by isrkik            #+#    #+#             */
/*   Updated: 2025/01/23 22:05:33 by amabrouk         ###   ########.fr       */
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
	while (line[*i])
	{
		if (ft_isspace(line[*i]))
			(*i)++;
		else
			break ;
	}
}
