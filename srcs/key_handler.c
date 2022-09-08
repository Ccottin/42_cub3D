/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 20.05/09/06 18:13:48 by ybendavi          #+#    #+#            */
/*   Updated: 2022/09/08 00:14:36 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	key_left(t_data *data)
{
	double	x;
	double	planx;

	x = data->caster.dirplayerx;
	planx = data->caster.planex;
	data->caster.dirplayerx = data->caster.dirplayerx * cos(-0.035)
		- data->caster.dirplayery * sin(-0.035);
	data->caster.dirplayery = x * sin(-0.035)
		+ data->caster.dirplayery * cos(-0.035);
	data->caster.planex = data->caster.planex * cos(-0.035)
		- data->caster.planey * sin(-0.035);
	data->caster.planey = planx * sin(-0.035)
		+ data->caster.planey * cos(-0.035);
	reload_img(data);
	return (0);
}

int	move_forward(t_data *data)
{
	double	mspeed;
	int		x_next;
	int		y_next;

	mspeed = 0.05;
	x_next = data->caster.playerx + data->caster.dirplayerx * mspeed;
	y_next = data->caster.playery + data->caster.dirplayery * mspeed;
	if (check_map_end(x_next, y_next, data) == 0)
	{
		data->caster.playerx = data->caster.playerx
			+ data->caster.dirplayerx * mspeed;
		data->caster.playery = data->caster.playery
			+ data->caster.dirplayery * mspeed;
		reload_img(data);
	}
	return (0);
}

int	move_left(t_data *data)
{
	double	mspeed;
	int		x_next;
	int		y_next;

	mspeed = 0.05;
	x_next = data->caster.playerx + data->caster.dirplayery * mspeed;
	y_next = data->caster.playery - data->caster.dirplayerx * mspeed;
	if (check_map_end(x_next, y_next, data) == 0)
	{
		data->caster.playerx = data->caster.playerx
			+ data->caster.dirplayery * mspeed;
		data->caster.playery = data->caster.playery
			- data->caster.dirplayerx * mspeed;
		reload_img(data);
	}
	return (0);
}

int	move_right(t_data *data)
{
	double	mspeed;
	int		x_next;
	int		y_next;

	mspeed = 0.05;
	x_next = data->caster.playerx - data->caster.dirplayery * mspeed;
	y_next = data->caster.playery + data->caster.dirplayerx * mspeed;
	if (check_map_end(x_next, y_next, data) == 0)
	{
		data->caster.playerx = data->caster.playerx
			- data->caster.dirplayery * mspeed;
		data->caster.playery = data->caster.playery
			+ data->caster.dirplayerx * mspeed;
		reload_img(data);
	}
	return (0);
}

int	move_backward(t_data *data)
{
	double	mspeed;
	int		x_next;
	int		y_next;

	mspeed = 0.05;
	x_next = data->caster.playerx - data->caster.dirplayerx * mspeed;
	y_next = data->caster.playery - data->caster.dirplayery * mspeed;
	if (check_map_end(x_next, y_next, data) == 0)
	{
		data->caster.playerx = data->caster.playerx
			- data->caster.dirplayerx * mspeed;
		data->caster.playery = data->caster.playery
			- data->caster.dirplayery * mspeed;
		reload_img(data);
	}
	return (0);
}
