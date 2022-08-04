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
	data->map_size = 0;
	data->map = NULL;
	data->north_texture = NULL;
	data->south_texture = NULL;
	data->east_texture = NULL;
	data->west_texture = NULL;
	data->floor_color.red = -1;
	data->floor_color.green = -1;
	data->floor_color.blue = -1;
	data->ceiling_color.red = -1;
	data->ceiling_color.green = -1;
	data->ceiling_color.blue = -1;
}
