#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42.h"
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>


# define ROWS 15
# define COLUMNS 20
# define TILE_SIZE 32
# define WIDTH 640
# define HEIGHT 480
# define FOV M_PI / 3
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif


typedef struct s_player {
	double		x;
	double		y;
	int 	radius;
	double	angle;
}		t_player;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			map[15][20];
	t_player	player;
	int			rows;
	int			columns;
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
	double	horz;
	double	vert;
}	t_ray;

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
	char	**map;
	int 	f_color;
	int 	c_color;
	int		len_columns;
	int		len_rows;
	t_utils flag_utils;
}	t_pars;


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
void	draw_map(t_game *game);
void	draw_player(t_game *game);
void	key_hook(mlx_key_data_t keydata, void *param);
// void	draw_line(t_game *game, int x1, int y1, int color);

#endif
