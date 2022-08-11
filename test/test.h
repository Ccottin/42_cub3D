#ifndef TEST_H
# define TEST_H

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
	int	player_x;
	int	player_y;
	int	planex;
	int	planey;
	int	fov;
	int	lengh_plane;
	int	screen_l;
	int	screen_w;
	int	wall_size;
	}	t_map;

#endif
