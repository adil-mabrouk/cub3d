/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:17:54 by amabrouk          #+#    #+#             */
/*   Updated: 2025/01/22 11:35:40 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "MLX42.h"
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>

# define TILE_SIZE 32
# define WIDTH 1200
# define HEIGHT 850
# define FOV M_PI / 3
# define BUFFER_SIZE 4
# define DOOR_OPEN 3


typedef struct s_sprite
{
	mlx_texture_t *frames[10]; 
	mlx_texture_t *current;
    int current_frame;    
    int frame_counter;
	bool	show_sprite;
	unsigned int tex_x;
    unsigned int tex_y;
	unsigned int y;
    unsigned int x;
	
} t_sprite;

typedef struct s_player {
	double		x;
	double		y;
	int 	radius;
	double	angle;
}		t_player;

typedef struct s_utils
{
	int	flag_ea;
	int	flag_we;
	int	flag_so;
	int	flag_no;
	int	colors;
	int	half;
}	t_utils;

typedef struct s_textures {
    mlx_texture_t *north;
    mlx_texture_t *south;
    mlx_texture_t *east;
    mlx_texture_t *west;
	mlx_texture_t *door;
} t_textures;


typedef struct s_pars
{
	char		*north;
	char		*west;
	char		*east;
	char		*south;
	char		**map;
	int 		f_color;
	int 		c_color;
	int			len_columns;
	int			len_rows;
	t_player	player;
	t_utils 	flag_utils;
}	t_pars;


typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_textures textures;
	t_pars		*pars;
	int			width;
	int			height;
	t_sprite	sprite;
}	t_game;


typedef struct s_ray
{
	double	angle;
	int		is_facing_down;
	int		is_facing_up;
	int		is_facing_right;
	int		is_facing_left;
	double	hor_wall_hit_x;
	double	hor_wall_hit_y;
	double  vert_wall_hit_x;
    double  vert_wall_hit_y;
	double	horz;
	double	vert;
	mlx_texture_t  *wall_texture;
}				t_ray;

//parsing

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
int		valid_colors(char *line, int *i, t_pars	*pars, bool color);
int		first_half(char *av, t_pars	*pars);
void	skip_spaces(char *line, int *i);
int		check_colors(char *line, int *i, t_pars *pars);
void	copy_to_2d(int len, char ***line, int fd2);
void	pars_file(char **line, t_pars *pars);
int		ft_strnewline(char *str);
int		pars_line(char *line, t_pars *pars);

//execution

void	ft_raycast(t_game *game);
void	init_game(t_game *game);
// void	draw_map(t_game *game);
// void	draw_player(t_game *game);
void	render_textured_wall(t_game *game, t_ray *ray, int column, double wall_height);
void 	loop_hook(void *param);
void 	render_sprite(t_game *game);
void 	init_sprite(t_game *game);
void 	key_handler(mlx_key_data_t keydata, void *param);
#endif