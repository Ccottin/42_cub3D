/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:24:17 by ccottin           #+#    #+#             */
/*   Updated: 2022/09/01 23:44:51 by ccottin          ###   ########.fr       */
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
	//	printf("casex = %d case y = %d c = %c\n", data->caster.casex, data->caster.casey, data->map.map[data->caster.casey][data->caster.casex]);
		if (data->map.map[data->caster.casey][data->caster.casex] && 
			data->map.map[data->caster.casey][data->caster.casex] == '1')
			wall = 1;
	}
	if (data->caster.side == 1)
		*distx -= data->caster.addx;
	else
		*disty -= data->caster.addy;
}

void	get_texture(t_data *data)//disty = -1
{
	data->caster.wallhit -= (int)data->caster.wallhit;
	data->caster.texposx = (double)data->north.width * data->caster.wallhit;
	data->caster.texposy = 0;
  }

unsigned long createRGB(int r, int g, int b)
{
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

void	draw_ceiling_floor(int start, t_data *data, int x, int end)
{
	int	i;

	i = 0;
	while (i < start)
	{
		pixel_to_image(data, x, i, createRGB(data->map.ceiling_color.red, data->map.ceiling_color.green, data->map.ceiling_color.blue));
		i++;
	}
	while (i < end)
		i++;
	while (i < data->caster.screen_w)
	{
		pixel_to_image(data, x, i, createRGB(data->map.floor_color.red, data->map.floor_color.green, data->map.floor_color.blue));
		i++;
	}
}

void	draw_line(t_data *data, double dist, int x)
{
	float	line;
	int	start;
	int	end;
	double	stepy;

	line = ((float)data->caster.screen_w / dist); //on peut le laisser en float?
	start = data->caster.middle_w - line / 2;
	end = data->caster.middle_w + line / 2;
	if (start < 0)
		start = 0;
	if (end > data->caster.screen_w)
		end = data->caster.screen_w - 1;
	get_texture(data);
	stepy = 1.0 * (double)data->north.height / line;
	draw_ceiling_floor(start, data, x, end);
	while (start < end)
  {
		if (data->caster.side == 1)
		pixel_to_image(data, x, start, data->north.addr[((int)data->caster.texposy * data->north.width + (int)data->caster.texposx) * 4] & 8355711);
		else
		pixel_to_image(data, x, start, data->north.addr[((int)data->caster.texposy * data->north.width + (int)data->caster.texposx) * 4]);
		data->caster.texposy += stepy;
		start++;
	}
}

int	get_img(t_data *data)
{
	int	start;
	double	distx;
	double	disty;

	start = 0;
	if (init_img(&(data->img0), data, 0)) //modifier en fonction de auelle image on dessine
		return (-1);
	while (start < data->caster.screen_l)
	{
		data->caster.camerax = 2 * start
			/ (double)data->caster.screen_l - 1;	
		data->caster.raydirx = data->caster.dirplayerx
			+ data->caster.planex * data->caster.camerax;
		data->caster.raydiry = data->caster.dirplayery
			+ data->caster.planey * data->caster.camerax;
		search_wall(data, &distx, &disty);
		if (data->caster.side == 1)
		{
//<<<<<<< truc
			data->caster.wallhit = data->caster.playery + distx * data->caster.raydiry;
//=======
//			data->caster.wallhit = data->caster.playerx + distx * data->caster.raydirx;
//>>>>>>> master
			draw_line(data, distx, start);
		}
		else
		{
//<<<<<<< truc
			data->caster.wallhit = data->caster.playerx + disty * data->caster.raydirx;
			draw_line(data, disty, start);
		}
//=======
//			data->caster.wallhit = data->caster.playery + disty * data->caster.raydiry;
	//		draw_line(data, disty, start);
	//	}
//>>>>>>> master
		set_null_caster(data);
		start++;
	}
	return (0);
}

int	raycaster(t_data *data)
{
	set_caster(data);
	if (init_mlx(data))
		return (-1);
	data->north.img = mlx_xpm_file_to_image(data->win.mlx, "wall.xpm",
			&data->north.width, &data->north.height);
	if (!data->north.img)
		return (-1);
	if (init_img(&data->north, data, 1))
		return (-1);
	if (get_img(data))
		return (-1);
	mlx_put_image_to_window(data->win.mlx, data->win.win, data->img0.img, 0, 0);
	events_handler(data);
	mlx_loop(data->win.mlx);
	return (0);
}
