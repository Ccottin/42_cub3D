#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <mlx.h>
# include <stdlib.h>
# include <errno.h>

typedef struct s_win {
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	}	t_win;

typedef struct s_color {
	int	red;
	int	green;
	int	blue;
	}	t_color;

typedef struct	s_player {
	int	player_x;
	int	player_y;
	char	player_facing;
	} t_player;

typedef struct s_map {
	char	**map;
	int	map_size;
	int	map_width;
	char	*north_texture;
	char	*south_texture;
	char	*east_texture;
	char	*west_texture;
	t_color	floor_color;
	t_color	ceiling_color;
	t_player	player;
	char	c;
	}	t_map;

typedef struct s_data {
	t_map	map;
	t_win	win;
	}	t_data;

char	*ft_strdup2(char *s, int size);
int	detach_map(t_data *data);
int	ft_strlen(char *str);
int	is_char_map(char c);
int	is_char_acter(char c);
int	ft_atoi(const char *nptr);
int	set_info(t_data *data);
int	init_map(char *av, t_data *data);
int	all_info_set(t_data *data);
int	get_info_wall_0(t_data *data, char *str, int i, char c);
int	get_info_wall_1(t_data *data, char *str, int i, char c);
int	get_info_wall(t_data *data, char *str, int i);
void	free_map(t_data *data);
void	free_all(t_data *data);
void	ft_return(int ret, t_data *data);
void	set_null(t_data *data);
void	*ft_calloc(size_t nmem);

#endif
