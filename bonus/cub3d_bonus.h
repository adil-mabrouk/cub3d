/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:17:54 by amabrouk          #+#    #+#             */
/*   Updated: 2025/01/26 12:12:46 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../MLX42.h"
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>

# define TILE_SIZE 32
# define WIDTH 1920
# define HEIGHT 1080
# define MINI_MAP_WIDTH 160
# define MINI_MAP_HEIGHT 160
# define SPEED 5
# define FOV M_PI
# define BUFFER_SIZE 4
# define DOOR_OPEN 3

typedef struct s_sprite
{
	mlx_texture_t	*frames[10];
	mlx_texture_t	*current;
	int				current_frame;
	int				frame_counter;
	bool			show_sprite;
	unsigned int	tex_x;
	unsigned int	tex_y;
	unsigned int	y;
	unsigned int	x;
}	t_sprite;

typedef struct s_player
{
	double		x;
	double		y;
	double		angle;
}	t_player;

typedef struct s_utils
{
	int	flag_ea;
	int	flag_we;
	int	flag_so;
	int	flag_no;
	int	colors;
	int	half;
	int	first_i;
	int	n;
	int	hold;
	int	fd;
}	t_utils;

typedef struct s_tex_utils
{
	double	tex_x;
	double	tex_y;
	double	tex_y_step;
	double	wall_top;
	double	wall_bottom;
}	t_tex_utils;

typedef struct s_textures
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	mlx_texture_t	*door;
}	t_textures;

typedef struct s_pars
{
	char		*north;
	char		*west;
	char		*east;
	char		*south;
	char		**map;
	int			f_color;
	int			c_color;
	int			len_columns;
	int			len_rows;
	t_player	player;
	t_utils		utils;
}	t_pars;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*mini_map;
	t_textures	textures;
	t_pars		*pars;
	t_sprite	sprite;
	t_tex_utils	tex_utils;
	int			width;
	int			height;
}	t_game;

typedef struct s_ray
{
	double			angle;
	bool			is_facing_down;
	bool			is_facing_up;
	bool			is_facing_right;
	bool			is_facing_left;
	double			hor_wall_hit_x;
	double			hor_wall_hit_y;
	double			vert_wall_hit_x;
	double			vert_wall_hit_y;
	double			horz;
	double			vert;
	double			x_inter;
	double			y_inter;
	double			x_step;
	double			y_step;
	mlx_texture_t	*wall_texture;
}	t_ray;

typedef struct s_coordinate
{
	int		j;
	int		k;
	int		y;
	int		x;
	bool	f;
}	t_cordinate;

/*             parsing                 */

void	ft_error(char *str, int fd);
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
void	copy_to_2d(int len, char ***line, int fd2, t_pars *pars);
void	pars_file(char **line, t_pars *pars);
int		ft_strnewline(char *str);
int		pars_line(char *line, t_pars *pars);
size_t	ft_strnewlen(char *str);
int		ft_strnewline(char *str);
void	skip_spaces(char *line, int *i);
int		no_newline(char *str);
int		count_biggest_len(char **line, int i);
int		check_right(char **line, int i);
int		last_line(char **line, int i);
int		check_below(char **line, int i);
int		mofm(char **line, int i, t_pars *pars);
int		check_mofm(t_pars *pars);
int		check_space_first(char **line, int *i);
int		ft_players(int c, t_pars *pars);
int		check_player(t_pars *pars, int i, int *j, int *dupl);
void	cpy_map(char **line, int length, t_pars *pars);
int		check_door(char **map, int i, int j);
void	ft_free_all(char **line);
void	ft_putstr_fd(char *str, int fd);
void	read_file(int fd2, int len, char ***line);
void	open_file(char *av, int *fd, int *fd2);
void	init_vars(t_pars *pars, int *i);
void	free_dom(char **s, int count);

/*            execution                */

void	ft_raycast(t_game *game);
void	init_game(t_game *game);
void	draw_player(t_game *game, int px, int py, int ray);
void	render_textured_wall(t_game *game, t_ray *ray,
			int column, double wall_height);
void	loop_hook(void *param);
void	render_sprite(t_game *game);
void	init_sprite(t_game *game);
void	key_handler(mlx_key_data_t keydata, void *param);
void	mouse_hook(double curr_x_pos, double curr_y_pos, void *param);
void	load_texture(mlx_texture_t **texture, char *path);
void	handle_keys(t_game *game);
void	x_button(void *param);
int		hit_wall(t_game *game, double x, double y);
int		get_rgb(int r, int g, int b);
double	ver_inter(t_game *game, t_ray *ray);
double	horz_inter(t_game *game, t_ray *ray);
double	norm_angle(t_ray *ray);
double	distance(t_game *game, double x, double y);
int		get_color(t_game *game, int x, int y);
void	render_floor(t_game *game, int column, double wall_bottom);
void	render_ceiling(t_game *game, int column, double wall_height);
void	render_minimap(t_game *game);

#endif