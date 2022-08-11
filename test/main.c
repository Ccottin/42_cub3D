#include "test.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	pixel_to_image(t_map *set, int x, int y, int color)
{
	char	*dst;
	
	dst = set->img.addr + (y * set->img.line_length + x * (set->img.bpx / 8));
	*(unsigned int*)dst = color;
}

char	*ft_strdup(const char *s)
{
	char	*ret;
	int	i;

	ret = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

void	*ft_calloc(int size)
{
	char	*ptr;
	int	i;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		ptr[i] = 0;
		i++;
	}
	return ((void*)ptr);
}

char	**map_init(void)
{
	char	**map;

	if (!(map = ft_calloc(sizeof(char*) * 6)))
		return (NULL);
	if (!(map[0] = ft_strdup("111111")))
		return (NULL);
	if (!(map[1] = ft_strdup("100001")))
		return (NULL);
	if (!(map[2] = ft_strdup("10P001")))
		return (NULL);
	if (!(map[3] = ft_strdup("100001")))
		return (NULL);
	if (!(map[4] = ft_strdup("111111")))
		return (NULL);
	return (map);
}

void	set_struct(t_map *set)
{
	set->wall_size = 96;	
	set->player_x = 3 * set->wall_size + (set->wall_size / 2);
	set->player_y = 3 * set->wall_size + (set->wall_size / 2);
	set->fov = 70;
	set->screen_l = 640;
	set->screen_w = 400;
	set->lengh_plane = (set->screen_l / 2) / tan(set->fov / 2);
}

int	check_horizontal(t_map *set, int ray, int *x, int *y, char **map)
{	
	int	starty;
	int	casey;
	int	startx;
	int	casex;
	int	addx;

	(void)ray;
	starty = (set->player_y / set->wall_size);
	starty = starty * set->wall_size - 1;
	casey = starty / set->wall_size;
	startx = set->player_x + (set->player_y - starty) / tan(set->fov / 2);
	casex = startx / set->wall_size;
	printf(" HORI\nx : case = %d, start = %d\ny : case = %d, start = %d\n", casex, startx, casey, starty);
	if (map[casex][casey] == '1')
	{
		*x = casex;
		*y = casey;
		return (1);
	}
	addx = tan(set->fov / 2) / set->wall_size;
	while (map[casex][casey] != '1')
	{
		starty = starty - set->wall_size;
		startx = startx + addx;
		casey = starty / set->wall_size;
		casex = startx / set->wall_size;
	}
	*x = casex;
	*y = casey;
	return (0);
	
}

int	check_vertical(t_map *set, int ray, int *x, int *y, char **map)
{
	int	starty;
	int	casey;
	int	startx;
	int	casex;
	int	addy;

	(void)ray;
	startx = set->player_x / set->wall_size;
	startx = startx * set->wall_size + 64;
	starty = set->player_y + (set->player_x - startx) / tan(set->fov / 2);
	casex = startx / set->wall_size;
	casey = starty / set->wall_size;
	printf("VERTI\nx : case = %d, start = %d\ny : case = %d, start = %d\n", casex, startx, casey, starty);
	if (map[casex][casey] == '1')
	{
		*x = casex;
		*y = casey;
		return (1);
	}
	addy = set->wall_size * tan(set->fov / 2);
	while (map[casex][casey] != '1')
	{
		starty = starty - addy;
		startx = startx + set->wall_size;
		casey = starty / set->wall_size;
		casex = startx / set->wall_size;
	}
	*x = casex;
	*y = casey;
	return (0);


}
//first step to round down player pos so we can avoid float, then we find player is on y = 2 on map

void	calculate_ray(t_map *set, int ray, int *x, int *y, char **map)
{
	int	hx;
	int	hy;
	int	vx;
	int	vy;

	check_horizontal(set, ray, x, y, map);
	hx = *x;
	hy = *y;
	check_vertical(set, ray, x, y, map);
	vx = *x;
	vy = *y;
	printf("case h = %d, %d ; case v = %d %d\n", hx, hy, vx, vy);
}

void	put_pixel(t_map *set, char **map)
{
	int	x;
	int	y;
	int	ray;
//	int	deg;

	set->img.addr = mlx_get_data_addr(set->img.img, &(set->img.bpx),
		&(set->img.line_length), &(set->img.endian));
	ray = 0;
	while (ray < set->screen_l)
	{
		x = 0;
		y = 0;
		calculate_ray(set, ray, &x, &y, map);
		pixel_to_image(set, x, y, 0x21D7DA);
		ray++;
	}
}

int	main(void)
{
	void	*mlx;
	void	*win;
	char	**map;
	t_map	set;

	mlx = mlx_init();
	if (!mlx)
		return (-1);
	set_struct(&set);
	win = mlx_new_window(mlx, set.screen_l, set.screen_w, "Hello World");
	if (!win)
		return (-1);
	map = map_init();
	if (!map)
		return (-1);
	set.img.img = mlx_new_image(mlx, set.screen_l, set.screen_w);
	put_pixel(&set, map);
	mlx_put_image_to_window(mlx, win, set.img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
