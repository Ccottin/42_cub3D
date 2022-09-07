/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:57:47 by ccottin           #+#    #+#             */
/*   Updated: 2022/09/07 23:28:12 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	draw_ceiling_floor(int start, t_data *data, int x, int end)
{
	int	i;

	i = 0;
	while (i < start && i < data->caster.screen_w && x < data->caster.screen_l)
	{
		pixel_to_image(data, x, i, create_rgb(data->map.ceiling_color.red,
				data->map.ceiling_color.green,
				data->map.ceiling_color.blue));
		i++;
	}
	while (i < end)
		i++;
	while (i < data->caster.screen_w && x < data->caster.screen_l)
	{
		pixel_to_image(data, x, i, create_rgb(data->map.floor_color.red,
				data->map.floor_color.green,
				data->map.floor_color.blue));
		i++;
	}
}

t_img	*get_texture(t_data *data)
{
	t_img	*img;

	if (data->caster.side == 1)
	{
		if (data->caster.casex > data->caster.playerx)
			img = &data->east;
		else
			img = &data->west;
	}
	else
	{
		if (data->caster.casey > data->caster.playery)
			img = &data->south;
		else
			img = &data->north;
	}
	data->caster.wallhit -= (int)data->caster.wallhit;
	data->caster.wallhit = fabs(1.0 - data->caster.wallhit);
	data->caster.texposx = (int)((double)img->width * data->caster.wallhit);
	if (data->caster.texposx >= img->width)
		data->caster.texposx = img->width - 1;
	if ((data->caster.side == -1 && data->caster.raydiry < 0)
		||(data->caster.side == 1 && data->caster.raydirx > 0))
		data->caster.texposx = img->width - data->caster.texposx - 1;
	return (img);
}

int	get_color(t_data *data, t_img *img)
{
	int	color;
	int	rgb;
  
	color = *(int*)(img->addr + ((int)data->caster.texposy * img->height
		+ data->caster.texposx) * 4);
	rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF);
	return (rgb);
}

void	draw_line2(t_data *data, int *start, int x, t_img *img)
{
	int	color;

	if (data->caster.texposy >= img->height)
		data->caster.texposy = img->height - 1;
	color = get_color(data, img);
	if (data->caster.side == 1)
		pixel_to_image(data, x, *start, (color >> 1) & 8355711);
	else
		pixel_to_image(data, x, *start, color);
	data->caster.texposy += data->caster.stepy;
	(*start)++;
}

void	draw_line(t_data *data, double dist, int x)
{
	double	line;
	int		start;
	int		end;
	t_img	*img;

	line = ((float)data->caster.screen_w / dist);
	start = data->caster.middle_w - (int)line / 2;
	end = data->caster.middle_w + (int)line / 2;
	if (start < 0)
		start = 0;
	if (end > data->caster.screen_w)
		end = data->caster.screen_w - 1;
	img = get_texture(data);
	draw_ceiling_floor(start, data, x, end);
	data->caster.stepy = 1.0 * (double)img->height / line;
	data->caster.texposy = (start - data->caster.middle_w + line / 2 + 1)
		* data->caster.stepy;
	while (start < end)
		draw_line2(data, &start, x, img);
}
