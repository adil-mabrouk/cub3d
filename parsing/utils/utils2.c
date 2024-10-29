/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:37:57 by isrkik            #+#    #+#             */
/*   Updated: 2024/10/29 09:41:07 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	o_verflow(unsigned long o_r, int sign)
{
	unsigned long	n_r;

	n_r = o_r * 10;
	if ((n_r / 10) != o_r)
	{
		if (sign < 0)
			return (0);
		return (-1);
	}
	return (-2);
}

int	check_space(const char *str, int i)
{
	while (str[i] && str[i] != '\n' && str[i] != ',')
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i] == '\0' || str[i] == '\n' || str[i] == ',')
			return (0);
		else
			return (1);
	}
	return (0);
}

int	ft_atoi(const char	*str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		if (o_verflow(result, sign) != -2)
			return (o_verflow(result, sign));
		result = result * 10 + str[i] - 48;
		i++;
	}
	if (check_space(str, i) == 1)
		ft_error("space between colors\n", 2);
	return (result * sign);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
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
