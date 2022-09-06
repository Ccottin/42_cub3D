/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 10:13:19 by ccottin           #+#    #+#             */
/*   Updated: 2022/09/06 19:28:32 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	set_caster(t_data *data)
{
	init_player(data);
	data->caster.screen_l = 860;
	data->caster.screen_w = 600;
	data->caster.middle_l = data->caster.screen_l / 2;
	data->caster.middle_w = data->caster.screen_w / 2;
}

int	init_mlx(t_data *data)
{
	data->win.mlx = mlx_init();
	if (!data->win.mlx)
		return (-1);
	data->win.win = mlx_new_window(data->win.mlx, data->caster.screen_l,
		data->caster.screen_w, "cub3D");
	if (!data->win.win)
		return (-1);
	return (0);
}

int	init_img(t_img *img, t_data *data, int mark)
{
	if (mark == 0)
		img->img = mlx_new_image(data->win.mlx, data->caster.screen_l,
			data->caster.screen_w);
	if (!img->img)
		return (-1);
	img->addr = mlx_get_data_addr(img->img, &(img->bpx),
		&(img->line_length), &(img->endian));
	return (0);
}

void	set_null_caster(t_data *data)
{
	data->caster.camerax = 0;
	data->caster.raydirx = 0;
	data->caster.raydiry = 0;
	data->caster.dirx = 0;
	data->caster.diry = 0;
	data->caster.addx = 0;
	data->caster.addy = 0;
	data->caster.side = 0;
}

void	set_null_imgs(t_data *data)
{
	data->img0.img = NULL;
	data->south.img = NULL;
	data->north.img = NULL;
	data->east.img = NULL;
	data->west.img = NULL;
	data->win.mlx = NULL;
	data->win.win = NULL;
}

void	set_null(t_data *data)
{
	errno = 0;
	data->map.map_size = 0;
	data->map.map_width = 0;
	data->map.map = NULL;
	data->map.north_texture = NULL;
	data->map.south_texture = NULL;
	data->map.east_texture = NULL;
	data->map.west_texture = NULL;
	data->map.floor_color.red = -1;
	data->map.floor_color.green = -1;
	data->map.floor_color.blue = -1;
	data->map.ceiling_color.red = -1;
	data->map.ceiling_color.green = -1;
	data->map.ceiling_color.blue = -1;
	data->caster.dirplayerx = 0;
	data->caster.dirplayery = 0;
	data->caster.planex = 0;
	data->caster.planey = 0;
	data->caster.casex = 0;
	data->caster.casey = 0;
	data->caster.playerx = 0;
	data->caster.playery = 0;
	data->caster.dirplayerx = 0;
	data->caster.dirplayery = 0;
	data->caster.planex = 0;
	data->caster.planey = 0;
	set_null_imgs(data);
	set_null_caster(data);
}
