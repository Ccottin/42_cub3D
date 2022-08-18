#include "test.h"
/*marchpo
		if (set->dirx < 0)
			px = (set->player_x - (cx * set->wall_size)) * add;
		else
			px = ((cx * set->wall_size) + set->wall_size - set->player_x);
		if (set->dirx < 0)
			px = (set->player_x - (cy * set->wall_size)) * add;
		else
			py = ((cx * set->wall_size) + set->wall_size - set->player_x);
*/

void	find_wall_h(t_map *set, float ray, int *x, int *y)
{
	int	cx;
	int	cy;
	int	px;
	int	py;
	float	add;

	cx = set->case_x;
	cy = set->case_y;
	if (set->dirx < 0)
		px = cx * set->wall_size - 1;
	else
		px = cx * set->wall_size + set->wall_size;
	py = set->player_y + (set->player_x - px) * tan(abs(ray) * M_PI / 180);
	cx = px / set->wall_size;
	cy = py / set->wall_size;
	add = (float)set->wall_size * tan(abs(ray) * M_PI / 180);
	printf("init = x = %d, y = %d\n", px, py);
	while (set->map[cx][cy] && set->map[cx][cy] != '1')
	{
		px = px + set->wall_size;
		py = py + add;
		cx = px / set->wall_size;
		cy = py / set->wall_size;
	}
	printf("x = %d, y = %d, cx = %d cy = %d add = %f\n", px, py, cx, cy, add);
	*x = cx;
	*y = cy;
}

void	get_proj(t_map *set, int dst, float ray)
{
	int	proj;
	int	start;
	int	end;
	int	i;
	float	fech;

	fech = (float)set->wall_size / (float)set->dist_plane;
	proj = dst * fech;
	printf("ray = %f proj = %d, dst = %d, fech = %f,  set->lengh_plane = %d\n\n\n", ray, proj, dst, fech, set->dist_plane);
	start = set->middle_w + (proj / 2);
	end = set->middle_w - (proj / 2);
	i = end;
	printf("start = %d,end = %d\n", start, end);
	printf("coucou\n");
	while (i < start)
	{
		pixel_to_image(set, ray, i, 0x00FF0000);
		i++;
	}
}

void	get_img(t_map *set)
{
	float	ray;
//	int	pix;
	int	start;
	int	x;
	int	y;
	int	dst;

	start = 0;
	ray = -(set->fov / 2);
	while (start < set->screen_l)
	{
		find_wall_h(set, ray, &x, &y);
//		find_wall_v(set, start, ray);
//		draw_line(set, start);(copié de l ancien)
		dst = sqrt((x - set->player_x) * (x - set->player_x)
			+ (y - set->player_y) * (y - set->player_y));
		get_proj(set, dst, ray);
		ray += (float)set->fov/(float)set->screen_l;
		start++;
		printf("ray = %f, start = %d\n", ray, start);
	}
}

void	set_struct(t_map *set)
{
	set->case_x = 2;
	set->case_y = 2;
	set->dirx = -1;
	set->diry = 1;
	set->wall_size = 64;	
	set->player_x = set->case_x * set->wall_size + (set->wall_size / 2);
	set->player_y = set->case_y * set->wall_size + (set->wall_size / 2);
	set->fov = 60;
	set->screen_l = 640;
	set->screen_w = 400;
	set->middle_l = set->screen_l / 2;
	set->middle_w = set->screen_w / 2;
	set->dist_plane = (set->screen_l / 2) / tan((set->fov / 2) * M_PI / 180);
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
