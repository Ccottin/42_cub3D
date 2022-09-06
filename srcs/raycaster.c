/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:24:17 by ccottin           #+#    #+#             */
/*   Updated: 2022/09/06 18:27:54 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	get_dist(t_data *data, double *distx, double *disty)
{
	if (data->caster.raydirx < 0)
	{
		data->caster.dirx = -1;
		*distx = (data->caster.playerx - data->caster.casex)
			* data->caster.addx;
	}
	else
	{
		data->caster.dirx = 1;
		*distx = (data->caster.casex + 1.0 - data->caster.playerx)
			* data->caster.addx;
	}
	if (data->caster.raydiry < 0)
	{
		data->caster.diry = -1;
		*disty = (data->caster.playery - data->caster.casey)
			* data->caster.addy;
	}
	else
	{
		data->caster.diry = 1;
		*disty = (data->caster.casey + 1.0 - data->caster.playery)
			* data->caster.addy;
	}
}

void	set_search(t_data *data, double *distx, double *disty, int *wall)
{
	*wall = 0;	
	data->caster.casex = (int)data->caster.playerx; //a voir ou on le met en fonction des calculs du mvt ptet chq debut de loop sufit
	data->caster.casey = (int)data->caster.playery;
	if (data->caster.raydirx == 0.00)
		data->caster.addx = 1 / 0.0000001;
	else
		data->caster.addx = fabs(1 / data->caster.raydirx);
	if (data->caster.raydiry == 0.00)
		data->caster.addy = 1/ 0.0000001;
	else
		data->caster.addy = fabs(1 / data->caster.raydiry);
	get_dist(data, distx, disty);
}

void	search_wall(t_data *data, double *distx, double *disty)
{
	int	wall;

	set_search(data, distx, disty, &wall);
	while (wall == 0)
	{
		if (*distx < *disty)
		{
			*distx += data->caster.addx;
			data->caster.side = 1;
			data->caster.casex += data->caster.dirx;
		}
		else
		{
			*disty += data->caster.addy;
			data->caster.side = -1;
			data->caster.casey += data->caster.diry;
		}
		if (data->caster.casey < 0 || data->caster.casex < 0 
			|| !data->map.map[data->caster.casey]
			|| !data->map.map[data->caster.casey][data->caster.casex])
			break;
		if (data->map.map[data->caster.casey][data->caster.casex] && 
			data->map.map[data->caster.casey][data->caster.casex] == '1')
			wall = 1;
	}
	if (data->caster.side == 1)
		*distx -= data->caster.addx;
	else
		*disty -= data->caster.addy;
}

t_img	*get_texture(t_data *data)
{
	t_img	*img;

	if (data->caster.side == 1)
	{
		if (data->caster.casex < data->caster.playerx)
			img = &data->east;
		else
			img = &data->west;
	}
	else
	{
		if (data->caster.casey > data->caster.playery)
			img = &data->south;
		else	
			img = &data->north;
	}
	data->caster.wallhit -= (int)data->caster.wallhit;
	data->caster.texposx =(int)((double)img->width * data->caster.wallhit);
	if ((data->caster.side == -1 && data->caster.raydiry < 0)
		||(data->caster.side == 1 && data->caster.raydirx > 0))
		data->caster.texposx = img->width - data->caster.texposx
			- 1;
	return (img);
  }

unsigned long createRGB(int r, int g, int b)
{
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

void	draw_ceiling_floor(int start, t_data *data, int x, int end)
{
	int	i;

	i = 0;
	while (i < start && i < data->caster.screen_w && x < data->caster.screen_l)
	{
		pixel_to_image(data, x, i, createRGB(data->map.ceiling_color.red,
			data->map.ceiling_color.green,
			data->map.ceiling_color.blue));
		i++;
	}
	while (i < end)
		i++;
	while (i < data->caster.screen_w && x < data->caster.screen_l)
	{
		pixel_to_image(data, x, i, createRGB(data->map.floor_color.red,
		data->map.floor_color.green,
		data->map.floor_color.blue));
		i++;
	}
}

int	get_color(t_data *data, t_img *img)
{
	int	color;
	int	rgb;

	color = *(int*)(img->addr
		+ ((int)data->caster.texposy * img->height
		+ (int)data->caster.texposx) * 4);
	rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF);
	return (rgb);
}

void	draw_line2(t_data *data, int *start, int x, t_img *img)
{
	int	color;

	if (data->caster.texposy >= img->height)
		data->caster.texposy = img->height - 1;
  	color = get_color(data, img);
	if (data->caster.side == 1)
		pixel_to_image(data, x, *start, (color >> 1) & 8355711);
	else
		pixel_to_image(data, x, *start, color);
	data->caster.texposy += data->caster.stepy;
	(*start)++;
}


void	draw_line(t_data *data, double dist, int x)
{
	float	line;
	int	start;
	int	end;
	t_img	*img;

	line = ((float)data->caster.screen_w / dist); 	
	start = data->caster.middle_w - line / 2;
	end = data->caster.middle_w + line / 2;
	if (start < 0)
		start = 0;
	if (end > data->caster.screen_w)
		end = data->caster.screen_w - 1;
	img = get_texture(data);
	draw_ceiling_floor(start, data, x, end);
	data->caster.stepy = 1.0 * (double)img->height / line;
	data->caster.texposy = (start - data->caster.middle_w + line / 2 + 1)
		* data->caster.stepy;
	while (start < end)
  		draw_line2(data, &start, x, img);
}

void	get_raydir(t_data *data, int start)
{
	data->caster.camerax = 2 * start
		/ (double)data->caster.screen_l - 1;
	data->caster.raydirx = data->caster.dirplayerx
		+ data->caster.planex * data->caster.camerax;
	data->caster.raydiry = data->caster.dirplayery
		+ data->caster.planey * data->caster.camerax;	
}

int	get_img(t_data *data)
{
	int	start;
	double	distx;
	double	disty;

	start = 0;
	if (init_img(&(data->img0), data, 0))
		return (-1);
	while (start < data->caster.screen_l)
	{
		get_raydir(data, start);
		search_wall(data, &distx, &disty);
		if (data->caster.side == 1)
		{
			data->caster.wallhit = data->caster.playery
				+ distx * data->caster.raydiry;
			draw_line(data, distx, start);
		}
		else
		{
			data->caster.wallhit = data->caster.playerx
				+ disty * data->caster.raydirx;
			draw_line(data, disty, start);
		}
		set_null_caster(data);
		start++;
	}
	return (0);
}

int	init_texture(t_data *data)
{
	data->north.img = mlx_xpm_file_to_image(data->win.mlx, 
	data->map.north_texture, &data->north.width, &data->north.height);
	data->south.img = mlx_xpm_file_to_image(data->win.mlx, 
	data->map.south_texture, &data->south.width, &data->south.height);
	data->east.img = mlx_xpm_file_to_image(data->win.mlx, 
	data->map.east_texture, &data->east.width, &data->east.height);
	data->west.img = mlx_xpm_file_to_image(data->win.mlx, 
	data->map.west_texture, &data->west.width, &data->west.height);
	if (!data->north.img || !data->south.img || !data->east.img
		|| !data->west.img)
		return (-1);
	if (init_img(&data->south, data, 1))
		return (-1);
	if (init_img(&data->north, data, 1))
		return (-1);
	if (init_img(&data->east, data, 1))
		return (-1);
	if (init_img(&data->west, data, 1))
		return (-1);
	return (0);
}

int	raycaster(t_data *data)
{
	set_caster(data);
	if (init_mlx(data))
		return (-1);
	if (init_texture(data))
		return (-1);
	free_init(data);
	if (get_img(data))
		return (-1);
	mlx_put_image_to_window(data->win.mlx, data->win.win, data->img0.img,
		0, 0);
	events_handler(data);
	mlx_loop(data->win.mlx);
	return (0);
}
