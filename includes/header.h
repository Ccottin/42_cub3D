#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <mlx.h>
# include <stdlib.h>
# include <errno.h>
# include <math.h>

typedef struct s_win {
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	}	t_win;

typedef struct s_img {
	void	*img;
	char	*addr;
	int	bpx;
	int	line_length;
	int	endian;
	int	width;
	int	height;
	}	t_img;

typedef struct s_color {
	int	red;
	int	green;
	int	blue;
	}	t_color;

typedef struct s_caster {
	double	playerx;
	double	playery;
	double	dirplayerx;
	double	dirplayery;
	double	planex;
	double	planey;
	double	camerax;
	double	raydirx;
	double	raydiry;
	double	stepy;
	double	dirx;
	double	diry;
	double	addx;
	double	addy;
	double	wallhit;
	double	texposy;
	int	casex;
	int	casey;
	int	screen_l;
	int	screen_w;
	int	middle_l;
	int	middle_w;
	int	texposx;
	int	side;
	}	t_caster;

typedef struct s_map {
	t_color	floor_color;
	t_color	ceiling_color;
	char	**map;
	int	map_size;
	int	map_width;
	char	*north_texture;
	char	*south_texture;
	char	*east_texture;
	char	*west_texture;
	char	c;
	}	t_map;

typedef struct s_data {
	t_map	map;
	t_win	win;
	t_img	img0;
	t_img	south;
	t_img	north;
	t_img	east;
	t_img	west;
	t_caster	caster;
	}	t_data;

char	*ft_strdup(char *s);
char	*ft_concat(char *s1, char *s2, int end);
void	*ft_calloc(size_t nmem);
unsigned long	create_rgb(int r, int g, int b);
int	events_handler(t_data *data);
int	key_right(t_data *data);
int	key_left(t_data *data);
int	move_forward(t_data *data);
int	move_left(t_data *data);
int	move_right(t_data *data);
int	move_backward(t_data *data);
int	check_map_end(int x_next, int y_next, t_data *data);
int	detach_map(t_data *data);
int	ft_strlen(char *str);
int	is_char_map(char c);
int	is_char_acter(char c);
int	ft_atoi(const char *nptr);
int	set_info(t_data *data);
int	init_map(char *av, t_data *data);
int	all_info_set(t_data *data);
int	get_img(t_data *data, int start);
int	get_info_wall_0(t_data *data, char *str, int i, char c);
int	get_info_wall_1(t_data *data, char *str, int i);
int	get_info_wall(t_data *data, char *str, int i);
int	init_mlx(t_data *data);
int	init_img(t_img *img, t_data *data, int mark);
int	raycaster(t_data *data);
int	malloc_gm_init(t_data *data, char **buffer, char *av);
int	check_last_char(t_data *data, char *buffer, int end);
int	ft_cpy(t_data *data, char *buffer, int start, int end);
int	init_texture(t_data *data);
int	map_closed(t_data *data);
void	get_dist(t_data *data, double *distx, double *disty);
void	draw_line(t_data *data, double dist, int x);
void	init_player(t_data *data);
void	reload_img(t_data *data);
void	free_map(t_data *data);
void	free_all(t_data *data);
void	ft_return(int ret, t_data *data);
void	set_null(t_data *data);
void	pixel_to_image(t_data *data, int x, int y, int color);
void	set_caster(t_data *data);
void	set_null_caster(t_data *data);
void	free_init(t_data *data);

#endif
