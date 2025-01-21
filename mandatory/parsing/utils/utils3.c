/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:38:40 by isrkik            #+#    #+#             */
/*   Updated: 2024/11/15 15:34:27 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

char	*ft_strdup(char *str)
{
	int		len;
	int		i;
	char	*dst;

	if (!str)
		return (NULL);
	i = 0;
	len = ft_strlen(str);
	dst = malloc(sizeof(char) * len + 1);
	if (!dst)
		return (NULL);
	while (i < len)
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strnjoin(char *s1, char	*s2, size_t n)
{
	size_t	lens1;
	size_t	lens2;
	char	*tmp;
	size_t	i;

	i = 0;
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	tmp = malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!tmp)
		return (free(tmp), free(s1), NULL);
	while (s1[i])
	{
		tmp[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] && i < n)
	{
		tmp[lens1] = s2[i];
		lens1++;
		i++;
	}
	tmp[lens1] = '\0';
	return (free(s1), tmp);
}

char	*ft_strchr(char *s, unsigned char c)
{
	while (*s)
	{
		if (c == *s)
			while (*s)
				return (*(&s));
		s++;
	}
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*tmp;
	int		i;
	size_t	lens1;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	lens1 = ft_strlen(s1);
	i = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!tmp)
		return (free(tmp), free(s1), NULL);
	while (s1[i])
	{
		tmp[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		tmp[lens1++] = s2[i++];
	}
	tmp[lens1] = '\0';
	return (free(s1), tmp);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	ft_strnewline(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}