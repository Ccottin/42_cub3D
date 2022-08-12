#include "test.h"

int	check_horizontal(t_map *set, int *x, int *y, char **map, int deg)
{	
	int	starty;
	int	casey;
	int	startx;
	int	casex;
	int	addx;

	starty = (set->player_y / set->wall_size) * set->wall_size - 1;
	casey = starty / set->wall_size;
	if (deg < 0)
		startx = set->player_x - (set->player_y - starty) / tan(abs(90 - deg) * M_PI / 180); //retuirer ecart y
	else	
		startx = set->player_x + (set->player_y - starty) / tan(abs(90 - deg) * M_PI / 180); //retuirer ecart y
	casex = startx / set->wall_size;
	printf("playerx = %d playery = %d, tan = %f, deg = %d\n", set->player_x, set->player_y, tan(abs(deg) * M_PI / 180), deg);
	printf(" HORI\nx : case = %d, start = %d\ny : case = %d, start = %d\n", casex, startx, casey, starty);
	if (map[casex][casey] == '1')
	{
		*x = startx;
		*y = starty;
		return (1);
	}
	addx = tan(abs(90 - deg) * M_PI / 180) / set->wall_size;
	while (map[casex][casey] != '1')
	{
		if (deg < 0)
			starty = starty - set->wall_size;
		if (deg > 0)
			starty = starty + set->wall_size;
		startx = startx - addx;
		casey = starty / set->wall_size;
		casex = startx / set->wall_size;
		printf("case = %c, y = %d, x = %d\n", map[casex][casey], casey, casex);
	}
	*x = startx;
	*y = starty;
	return (0);
	
}

int	check_vertical(t_map *set, int *x, int *y, char **map, int deg)
{
	int	starty;
	int	casey;
	int	startx;
	int	casex;
	int	addy;

	if (deg < 0)
		startx = (set->player_x / set->wall_size) * set->wall_size + set->wall_size;
	if (deg > 0)
		startx = (set->player_x / set->wall_size) * set->wall_size - 1;
	starty = set->player_y + (set->player_x - startx) / tan(abs(90 - deg) * M_PI / 180);
	casex = startx / set->wall_size;
	casey = starty / set->wall_size;
	printf("VERTI\nx : case = %d, start = %d\ny : case = %d, start = %d\n", casex, startx, casey, starty);
	if (map[casex][casey] == '1')
	{
		*x = startx;
		*y = starty;
		return (1);
	}
	addy = set->wall_size * tan(abs(deg) * M_PI / 180);
	while (map[casex][casey] != '1')
	{
		if (deg < 0)
			starty = starty - addy;
		if (deg > 0)
			starty = starty + addy;
		startx = startx + set->wall_size;
		casey = starty / set->wall_size;
		casex = startx / set->wall_size;
		printf("case = %c, y = %d, x = %d addy = %d\n", map[casex][casey], casey, casex, addy);
	}
	*x = startx;
	*y = starty;
	return (0);
}
//first step to round down player pos so we can avoid float, then we find player is on y = 2 on map

void	get_proj(t_map *set, int dst, int ray)
{
	int	proj;
	int	middle;
	int	start;
	int	end;
	int	i;
	float	fech;

	fech = (float)set->wall_size / (float)set->lengh_plane;
	proj = dst * fech;
	printf("ray = %d proj = %d, dst = %d, fech = %f,  set->lengh_plane = %d\n", ray, proj, dst, fech, set->lengh_plane);
	middle = set->screen_w / 2;
	start = middle + (proj / 2);
	end = middle - (proj / 2);
	i = end;
	printf("start = %d,end = %d\n", start, end);
	printf("coucou\n");
	while (i < start)
	{
		pixel_to_image(set, ray, i, 0x00FF0000);
		i++;
	}
}

void	calculate_ray(t_map *set, int ray, int *x, int *y, char **map, int deg)
{
	int	hx;
	int	hy;
	int	vx;
	int	vy;
	int	dst;

	check_horizontal(set, x, y, map, deg);
	hx = *x;
	hy = *y;
	check_vertical(set, x, y, map, deg);
	vx = *x;
	vy = *y;
	if (vx < hx)
		dst = sqrt((vx - set->player_x) * (vx - set->player_x)
			+ (vy - set->player_y) * (vy - set->player_y));
	else
		dst = sqrt((hx - set->player_x) * (hx - set->player_x)
			+ (hy - set->player_y) * (hy - set->player_y));
	get_proj(set, dst, ray);
}
void	put_pixel(t_map *set, char **map)
{
	int	x;
	int	y;
	int	ray;
	int	deg;
	int	dpp;

	set->img.addr = mlx_get_data_addr(set->img.img, &(set->img.bpx),
		&(set->img.line_length), &(set->img.endian));
	ray = 0;
	deg = -(set->fov / 2);
	dpp = set->screen_l / set->fov;
	printf("dpp= %d, calcu = %d\n", dpp, set->fov / set->screen_l);
	while (ray < set->screen_l)
	{
		x = 0;
		y = 0;
		calculate_ray(set, ray, &x, &y, map, deg);
		dpp--;
		if (dpp == 0)
		{
			deg++;
			dpp = set->screen_l / set->fov;
		}	
		ray++;
		printf("deg = %d, dpp = %d\n", deg, dpp);
	}
}

void	set_struct(t_map *set)
{
	set->wall_size = 96;	
	set->player_x = 3 * set->wall_size + (set->wall_size / 2);
	set->player_y = 3 * set->wall_size + (set->wall_size / 2);
	set->fov = 70;
	set->screen_l = 640;
	set->screen_w = 400;
	set->lengh_plane = (set->screen_l / 2) / tan((set->fov / 2) * M_PI / 180);
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
