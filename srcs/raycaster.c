/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:24:17 by ccottin           #+#    #+#             */
/*   Updated: 2022/09/01 23:19:49 by ybendavi         ###   ########.fr       */
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
		data->caster.addx = 1 / 2147483647;
	else
		data->caster.addx = fabs(1 / data->caster.raydirx);
	if (data->caster.raydiry == 0.00)
		data->caster.addy = 1/ 2147483647;
	else
		data->caster.addy = fabs(1 / data->caster.raydiry);
	get_dist(data, distx, disty);
}
//regler le soucis de la ligne au debut
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
		if (data->map.map[data->caster.casey][data->caster.casex] == '1')
			wall = 1;
	}
	if (data->caster.side == 1)
		*distx -= data->caster.addx;
	else
		*disty -= data->caster.addy;
}

void	draw_line(t_data *data, double dist, int x)
{
	int	line;
	int	start;
	int	end;
	int	i;

	line = ((float)data->caster.screen_w / dist);
	start = data->caster.middle_w - line / 2;
	end = data->caster.middle_w + line / 2;
	if (start < 0)
		start = 0;
	if (end > data->caster.screen_w)
		end = data->caster.screen_w - 1;
	i = start;
	if (data->caster.side == 1) //partie a modifier pour les textures
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
	}
}

int	get_img(t_data *data)
{
	int	start;
	double	distx;
	double	disty;

	start = 0;
	if (init_img(&(data->img0), data)) //modifier en fonction de auelle image on dessine
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
		printf("%d :: distx = %f, disty = %f\n", start, distx, disty);
		if (data->caster.side == 1)
			draw_line(data, distx, start);
		else
			draw_line(data, disty, start);
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
	if (get_img(data))
		return (-1);
	mlx_put_image_to_window(data->win.mlx, data->win.win, data->img0.img, 0, 0);
	events_handler(data);
	mlx_loop(data->win.mlx);
	return (0);
}
