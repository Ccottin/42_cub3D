/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:24:17 by ccottin           #+#    #+#             */
/*   Updated: 2022/09/01 18:41:26 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	

int	search_wall(t_map *set, double *distx, double *disty)
{
	double	addx;
	double	addy;
	int	dirx;
	int	diry;
	int	wall;
	int	side;

	data->caster.casex = (int)data->caster.playerx;
	data->caster.casey = (int)data->caster.playery;
	wall = 0;
	if (data->caster.raydirx == 0.00)
		addx = 1 / 2147483647;
	else
		addx = fabs(1 / data->caster.raydirx);
	if (data->caster.raydiry == 0.00)
		addy = 1/ 2147483647;
	else
		addy = fabs(1 / data->caster.raydiry);
	if (data->caster.raydirx < 0)
	{
		dirx = -1;
		*distx = (data->caster.playerx - data->caster.casex) * addx;
	}
	else
	{
		dirx = 1;
		*distx = (data->caster.casex + 1.0 - data->caster.playerx) * addx;
	}
	if (data->caster.raydiry < 0)
	{
		diry = -1;
		*disty = (data->caster.playery - data->caster.casey) * addy;
	}
	else
	{
		diry = 1;
		*disty = (data->caster.casey + 1.0 - data->caster.playery) * addy;
	}
	while (wall == 0)
	{
		if (*distx < *disty)
		{
			*distx += addx;
			side = 1;
			data->caster.casex += dirx;
		}
		else
		{
			*disty += addy;
			side = -1;
			data->caster.casey += diry;
		}
		if (data->caster.map[data->caster.casey][data->caster.casex] == '1')
			wall = 1;
	}
	if (side == 1)
		*distx -= addx;
	else
		*disty -= addy;
	return (side);
}

int	get_img(t_data *data)
{
	int	start;
	int	side;
	double	distx;
	double	disty;

	start = 0;
	while (start < data->caster.screen_l)
	{
		data->caster.camerax = 2 * start
			/ (double)data->caster.screen_l - 1;	
		data->caster.raydirx = data->caster.dirplayerx
			+ data->caster.planex * data->caster.camerax;
		data->caster.raydiry = data->caster.dirplayery
			+ data->caster.planey * data->caster.camerax;
		side = search_wall(data, &distx, &disty);
		if (side == 1)
			draw_line(data, distx, side, start);
		else
			draw_line(data, disty, side, start);
		start++;
	}
	return (side);
}

int	raycaster(t_data *data)
{
	set_caster(data);
	if (init_mlx(data))
		return (-1);
	return (0);
}
