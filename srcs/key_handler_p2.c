/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler_p2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 19:10:48 by ybendavi          #+#    #+#             */
/*   Updated: 2022/09/07 19:11:40 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_map_end(int x_next, int y_next, t_data *data)
{
	int	y;
	int	x;

	if (y_next < 0 || x_next < 0)
		return (1);
	y = 0;
	x = 0;
	while (data->map.map[y] && y < y_next)
		y++;
	if (y != y_next)
		return (1);
	if (data->map.map[y])
	{
		while (data->map.map[y][x] && x < x_next)
			x++;
	}
	if (data->map.map[y] && data->map.map[y][x] && x == x_next)
		return (0);
	return (1);
}

void	reload_img(t_data *data)
{
	mlx_destroy_image(data->win.mlx, data->img0.img);
	if (get_img(data))
		ft_return(-1, data);
	mlx_clear_window(data->win.mlx, data->win.win);
	mlx_put_image_to_window(data->win.mlx, data->win.win, data->img0.img, 0, 0);
}

int	key_right(t_data *data)
{
	double	x;
	double	planx;

	x = data->caster.dirplayerx;
	planx = data->caster.planex;
	data->caster.dirplayerx = data->caster.dirplayerx * cos(0.15)
		- data->caster.dirplayery * sin(0.15);
	data->caster.dirplayery = x * sin(0.15)
		+ data->caster.dirplayery * cos(0.15);
	data->caster.planex = data->caster.planex * cos(0.15)
		- data->caster.planey * sin(0.15);
	data->caster.planey = planx * sin(0.15) + data->caster.planey * cos(0.15);
	reload_img(data);
	return (0);
}
