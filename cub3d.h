/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:37:30 by isrkik            #+#    #+#             */
/*   Updated: 2024/11/18 16:36:10 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# include "MLX42.h"
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_player {
	double		x;
	double		y;
	int 	radius;
	float	angle;
}		t_player;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			map[15][20];
	t_player	player;
	int			tile_size;
	int			width;
	int			height;
	int			rows;
	int			colums;
}	t_game;

typedef struct s_utils
{
	int	flag_ea;
	int	flag_we;
	int	flag_so;
	int	flag_no;
	int	colors;
	int	half;
}	t_utils;

typedef struct s_pars
{
	char	*north;
	char	*west;
	char	*east;
	char	*south;
	char	**temp;
	int f_color;
	int c_color;
	t_utils flag_utils;
}	t_pars;


void    ft_error(char *str, int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *s, unsigned char c);
char	*ft_strnjoin(char *s1, char	*s2, size_t n);
char	*ft_strdup(char *str);
int		ft_strlen(char *str);
char	*get_next_line(int fd);
int		ft_strcmp(char *s1, char *s2);
char	*ft_substr(char *s, int start, int len);
int		ft_isdigit(int c);
int		ft_atoi(const char	*str);
int		ft_isspace(int c);
void	valid_colors(char *line, int *i, t_pars	*pars, bool color);
int		first_half(char *av, t_pars	*pars);
void	skip_spaces(char *line, int *i);
void	check_colors(char *line, int *i, t_pars *pars);
void	copy_to_2d(int len, char ***line, int fd2);
void	pars_file(char **line, t_pars *pars);
int		ft_strnewline(char *str);

#endif