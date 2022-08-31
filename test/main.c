#include "test.h"

int	search_wall(t_map *set, double *distx, double *disty)
{
	double	addx;
	double	addy;
	int	dirx;
	int	diry;
	int	wall;
	int	side;

	set->casex = (int)set->playerx;
	set->casey = (int)set->playery;
	wall = 0;
	if (set->raydirx == 0.00)
		addx = 1 / 2147483647;
	else
		addx = fabs(1 / set->raydirx);
	if (set->raydiry == 0.00)
		addy = 1/ 2147483647;
	else
		addy = fabs(1 / set->raydiry);
	if (set->raydirx < 0)
	{
		dirx = -1;
		*distx = (set->playerx - set->casex) * addx;
	}
	else
	{
		dirx = 1;
		*distx = (set->casex + 1.0 - set->playerx) * addx;
	}
	if (set->raydiry < 0)
	{
		diry = -1;
		*disty = (set->playery - set->casey) * addy;
	}
	else
	{
		diry = 1;
		*disty = (set->casey + 1.0 - set->playery) * addy;
	}
	printf("init :: disty = %f addy = %f, distx = %f addy = %f\t", *disty, addy, *distx, addx);
	while (wall == 0)
	{
		if (*distx < *disty)
		{
			*distx += addx;
			side = 1;
			set->casex += dirx;
		}
		else
		{
			*disty += addy;
			side = -1;
			set->casey += diry;
		}
		printf("casex = %d, casey = %d, char = %c\n", set->casex, set->casey, set->map[set->casey][set->casex]);
		if (set->map[set->casey][set->casex] == '1')
			wall = 1;
	}
/*	if (side == 1) //crrige le fisheye mqis pobien compris, si ca vient po on fera un ptit coup de trigo
		*distx -= addx;
	else
		*disty -= addy;*/
	return (side);
}

void	draw_line(t_map *set, double dist, int side, int x)
{
	int	line;
	int	start;
	int	end;
	int	i;

	printf("%d :: dist = %f\n", x, dist);
	line = ((float)set->screen_w / dist);
	start = set->middle_w - line / 2;
	end = set->middle_w + line / 2;
	if (start < 0)
		start = 0;
	if (end > set->screen_w)
		end = set->screen_w - 1;
	i = start;
	if (side == 1)
	{
		while (i < end)
		{
			pixel_to_image(set, x, i, 0x00FF0000);
			i++;
		}
	}
	else
	{
		while (i < end)
		{
			pixel_to_image(set, x, i, 0x00FF0001);
			i++;
		}
	}
}

int	get_img(t_map *set)
{
	int	start;
	int	side;
	double	distx;
	double	disty;

	start = 0;
	while (start < set->screen_l)
	{
		printf("%d ::", start);
		set->camerax = 2 * start / (double)set->screen_l - 1;	
		set->raydirx = set->dirplayerx + set->planex * set->camerax;
		set->raydiry = set->dirplayery + set->planey * set->camerax;
		printf("rayx = %f, rayy = %f ; ", set->raydirx, set->raydiry);
		side = search_wall(set, &distx, &disty);
	//	if (side == 1)
	//		draw_line(set, distx, side, start);
	//	else
	//		draw_line(set, disty, side, start);
		start++;
	}
	return (side);
}

void	set_struct(t_map *set)
{
	set->playerx = 1;
	set->playery = 1;
	set->dirplayerx = 0;
	set->dirplayery = 0;
	set->planex = 0;
	set->planey = 0.6;
	set->wall_size = 64;
	set->screen_l = 860;
	set->screen_w = 600;
	set->middle_l = set->screen_l / 2;
	set->middle_w = set->screen_w / 2;
}

int	main(void)
{
	void	*mlx;
	void	*win;
	t_map	set;

	mlx = mlx_init();
	if (!mlx)
		return (-1);
	set_struct(&set);
	set.map = map_init();
	if (!set.map)
		return (-1);
	win = mlx_new_window(mlx, set.screen_l, set.screen_w, "Hello World");
	if (!win)
		return (-1);
	set.img.img = mlx_new_image(mlx, set.screen_l, set.screen_w);
	set.img.addr = mlx_get_data_addr(set.img.img, &(set.img.bpx),
		&(set.img.line_length), &(set.img.endian));
	get_img(&set);
	mlx_put_image_to_window(mlx, win, set.img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
