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
/*	if (data->caster.side == 1) //partie a modifier pour les textures
	{
		while (i < end)
		{
			pixel_to_image(data, x, i, 0xFF08F7F0);
			i++;
		}
	}
	else
	{
		while (i < end)
		{
			pixel_to_image(data, x, i, 0xFFFFF01F);
			i++;
		}
	}*/

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dest1;
	unsigned char	*src1;
	size_t			i;

	i = 0;
	if (!(dest) && !(src))
		return (0);
	dest1 = (unsigned char *)dest;
	src1 = (unsigned char *)src;
	while (i < n)
	{
		dest1[i] = src1[i];
		i++;
	}
	return (dest);
}

void	draw_line(t_data *data, double dist, int posx, int x)
{
	double	line;
	double	posy;
	double	stepy;
	int	text;
	int	start;
	int	end;
	int	*color;

	text = 0;
	line = ((float)data->caster.screen_w / dist); //on peut le laisser en float?
	stepy = 1.0 * (double)data->north.height / line;
	start = data->caster.middle_w - line / 2;
	end = data->caster.middle_w + line / 2;
	printf("line %f , step = %f", line, stepy);
	if (start < 0)
		start = 0;
	if (end > data->caster.screen_w)
		end = data->caster.screen_w - 1;
	posy = (start - data->caster.middle_w + line / 2) * stepy;
	printf("posy = %f", posy);
	color = ft_calloc(4);
	while (start < end)
	{
		text = (int)posy;// & (data->north.height - 1);
		posy += stepy;
		color = ft_memcpy(color, &(data->north.addr)[data->north.height * posx + text], 4);
//	printf("text = %d posy = %f, color %d\n", text, posy, *color);
	//	if (data->caster.side == 1)
	//		color = (color >> 1) & 8355711;
		pixel_to_image(data, x, start, *color);
		start++;
	}
	free(color);
}

int	set_texture(t_data *data, int x, double dist)
{
	int	posx;
	
	data->caster.wallhit -= (int) data->caster.wallhit;
	posx = (int)(data->caster.wallhit * (double)data->north.width);
	if ((data->caster.side == -1 && data->caster.raydiry < 0)
		||(data->caster.side == 1 && data->caster.raydirx > 0))
		posx = data->north.width - posx - 1;
	printf("%d :: data->caster.wallhit = %f, posx = %d",x , data->caster.wallhit, posx);
	draw_line(data, dist, posx, x);
	return (0);
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
		data->caster.camerax = 2 * start
			/ (double)data->caster.screen_l - 1;	
		data->caster.raydirx = data->caster.dirplayerx
			+ data->caster.planex * data->caster.camerax;
		data->caster.raydiry = data->caster.dirplayery
			+ data->caster.planey * data->caster.camerax;
		search_wall(data, &distx, &disty);
		if (data->caster.side == 1)
		{
			data->caster.wallhit = data->caster.playery + distx * data->caster.raydiry;
		//	draw_line(data, distx, start);
		}
		else
		{
			data->caster.wallhit = data->caster.playerx + disty * data->caster.raydirx;
		//	draw_line(data, disty, start);
		}
		if (set_texture(data, start, data->caster.wallhit))
			return (-1);
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
