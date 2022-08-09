/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 10:13:19 by ccottin           #+#    #+#             */
/*   Updated: 2022/08/04 21:28:27 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
}
