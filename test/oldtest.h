
#ifndef OLDTEST_H
# define OLDTEST_H

# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_img {
	void	*img;
	char	*addr;
	int	bpx;
	int	line_length;
	int	endian;
	}	t_img;

typedef struct s_map {
	t_img	img;
	char	**map;
	int	case_x;
	int	case_y;
	int	player_x;
	int	player_y;
	int	dirx;
	int	diry;
	int	planex;
	int	planey;
	int	fov;
	int	dist_plane;
	int	screen_l;
	int	screen_w;
	int	middle_l;
	int	middle_w;
	int	wall_size;
	}	t_map;


int	ft_strlen(const char *s);
void	pixel_to_image(t_map *set, int x, int y, int color);
char	*ft_strdup(const char *s);
void	*ft_calloc(int size);
char	**map_init(void);

#endif
