/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initcaster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 23:01:09 by ccottin           #+#    #+#             */
/*   Updated: 2022/09/07 23:05:09 by ccottin          ###   ########.fr       */
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

void	set_caster(t_data *data)
{
	init_player(data);
	data->caster.screen_l = 1001;
	data->caster.screen_w = 1001;
	data->caster.middle_l = data->caster.screen_l / 2;
	data->caster.middle_w = data->caster.screen_w / 2;
}
