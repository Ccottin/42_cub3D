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
	char	**map;
	int	casex;
	int	casey;
	double	playerx;
	double	playery;
	int	dirplayerx;
	int	dirplayery;
	double	planex;
	double	planey;
	double	camerax;
	double	raydirx;
	double	raydiry;
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
