/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initcaster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 23:01:09 by ccottin           #+#    #+#             */
/*   Updated: 2022/09/08 00:28:59 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

void	free_init(t_data *data)
{
	if (data->map.north_texture)
		free(data->map.north_texture);
	if (data->map.south_texture)
		free(data->map.south_texture);
	if (data->map.east_texture)
		free(data->map.east_texture);
	if (data->map.west_texture)
		free(data->map.west_texture);
	data->map.north_texture = NULL;
	data->map.south_texture = NULL;
	data->map.east_texture = NULL;
	data->map.west_texture = NULL;
}

void	set_caster(t_data *data)
{
	init_player(data);
	data->caster.screen_l = 860;
	data->caster.screen_w = 600;
	data->caster.middle_l = data->caster.screen_l / 2;
	data->caster.middle_w = data->caster.screen_w / 2;
}
