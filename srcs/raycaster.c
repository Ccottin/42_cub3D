/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:24:17 by ccottin           #+#    #+#             */
/*   Updated: 2022/09/08 00:27:35 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	set_search(t_data *data, double *distx, double *disty, int *wall)
{
	*wall = 0;
	data->caster.casex = (int)data->caster.playerx;
	data->caster.casey = (int)data->caster.playery;
	if (data->caster.raydirx == 0.00)
		data->caster.addx = 1 / 0.0000001;
	else
		data->caster.addx = fabs(1 / data->caster.raydirx);
	if (data->caster.raydiry == 0.00)
		data->caster.addy = 1 / 0.0000001;
	else
		data->caster.addy = fabs(1 / data->caster.raydiry);
	get_dist(data, distx, disty);
}

double	loop_search_wall(t_data *data, double add, char c)
{
	if (c == 'x')
	{
		data->caster.side = 1;
		data->caster.casex += data->caster.dirx;
	}
	else if (c == 'y')
	{
		data->caster.side = -1;
		data->caster.casey += data->caster.diry;
	}
	return (add);
}

void	search_wall(t_data *data, double *distx, double *disty)
{
	int	wall;

	set_search(data, distx, disty, &wall);
	while (wall == 0)
	{
		if (*distx < *disty)
			*distx += loop_search_wall(data, data->caster.addx, 'x');
		else
			*disty += loop_search_wall(data, data->caster.addy, 'y');
		if (data->caster.casey < 0 || data->caster.casex < 0
			|| !data->map.map[data->caster.casey]
			|| !data->map.map[data->caster.casey][data->caster.casex])
			break ;
		if (data->map.map[data->caster.casey][data->caster.casex]
				&& data->map.map[data->caster.casey][data->caster.casex] == '1')
			wall = 1;
	}
	if (data->caster.side == 1)
		*distx -= data->caster.addx;
	else
		*disty -= data->caster.addy;
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

int	get_img(t_data *data, int start)
{
	double	distx;
	double	disty;

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
