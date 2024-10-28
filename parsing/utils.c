/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:22:39 by isrkik            #+#    #+#             */
/*   Updated: 2024/10/28 18:43:39 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*sub;
	int		i;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		return (ft_strdup("\0"));
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (s[start] && len > 0)
	{
		sub[i] = s[start];
		start++;
		i++;
		len--;
	}
	sub[i] = '\0';
	return (sub);
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

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void    ft_putchar_fd(char c, int fd)
{
    write (fd, &c, 1);
}

void    ft_putstr_fd(char *str, int fd)
{
    int i;

    i = 0;
    while (str[i])
    {
        ft_putchar_fd(str[i], fd);
        i++;
    }
}

void    ft_error(char *str, int fd)
{
    ft_putstr_fd(str, fd);
    exit(EXIT_FAILURE);
}

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
