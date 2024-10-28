/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:47:08 by isrkik            #+#    #+#             */
/*   Updated: 2024/10/28 16:48:33 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	*ft_memset(void *b, int c, size_t len)
{
	char			*s;
	unsigned char	a;

	s = (char *)b;
	a = (unsigned char)c;
	while (len > 0)
	{
		*s = c;
		s++;
		len--;
	}
	return (b);
}

char	*ft_strcpy(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_line(char *new_line, char *line, char *store)
{
	size_t	length;

	if (new_line != NULL)
	{
		length = ft_strnewlen(store) + 1;
		line = ft_strnjoin(line, store, length);
		if (!line)
			return (free(line), NULL);
		store = ft_strcpy(store, new_line + 1);
		return (line);
	}
	line = ft_strjoin(line, store);
	if (!line)
		return (free(line), NULL);
	store = ft_memset(store, 0, ft_strlen(store));
	return (line);
}

char	*ft_read_join(char **line, char **store, int fd)
{
	int		bytes;
	char	*stock;
	char	*found;

	stock = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!stock)
		return (free(stock), NULL);
	stock[0] = '\0';
	while (1)
	{
		bytes = read(fd, stock, BUFFER_SIZE);
		if (bytes < 0)
			return (free(stock), free(*line), free(*store), *store = NULL, NULL);
		stock[bytes] = '\0';
		*store = ft_strjoin(*store, stock);
		if (!*store)
			return (free(stock), NULL);
		found = ft_strchr(*store, '\n');
		*line = ft_line(found, *line, *store);
		if (!*line)
			return (free(stock), free(*line), NULL);
		if (found || bytes == 0)
			break ;
	}
	return (free(stock), *line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*store;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(sizeof(char));
	if (!line)
		return (free(line), NULL);
	line[0] = '\0';
	line = ft_read_join(&line, &store, fd);
	if (!line)
		return (free(line), NULL);
	if (line[0] == '\0')
		return (free(line), free(store), store = NULL, NULL);
	return (line);
}
