/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:54:38 by ccottin           #+#    #+#             */
/*   Updated: 2022/09/07 18:58:54 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*fill_info_wall(char *str, int start, int end)
{
	char	*ret;
	int		i;

	ret = ft_calloc(end - start + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (start < end)
		ret[i++] = str[start++];
	return (ret);
}

int	get_info_wall_3(t_data *data, char *str, int i, int y)
{
	if (data->map.c == 'N')
	{
		if (data->map.north_texture)
			return (-5);
		data->map.north_texture = fill_info_wall(str, i, y);
	}
	else if (data->map.c == 'S')
	{
		if (data->map.south_texture)
			return (-5);
		data->map.south_texture = fill_info_wall(str, i, y);
	}	
	else if (data->map.c == 'W')
	{
		if (data->map.west_texture)
			return (-5);
		data->map.west_texture = fill_info_wall(str, i, y);
	}
	if ((data->map.c == 'S' && !data->map.south_texture) || (data->map.c == 'N'
		&& !data->map.north_texture) ||  (data->map.c == 'W' && !data->map.west_texture))
			return (-1);
	return (0);
}

int	get_info_wall_0(t_data *data, char *str, int i, char c)
{
	int	y;
	int	ret;

	data->map.c = c;
	while (str[i] && str[i] == ' ')
		i++;
	y = i;
	while (str[y] && (str[y] != ' ' && str[y] != 0))
		y++;
	ret = get_info_wall_3(data, str, i, y);
	if (ret)
		return (ret);
	while (str[y] && str[y] == ' ')
		y++;
	if (str[y] != 0)
		return (-5);
	return (0);
}

int	get_info_wall_1(t_data *data, char *str, int i)
{
	int	y;

	while (str[i] && str[i] == ' ')
		i++;
	y = i;
	while (str[y] && (str[y] != ' ' && str[y] != 0))
		y++;
	if (data->map.east_texture)
		return (-5);
	data->map.east_texture = fill_info_wall(str, i, y);
	if (!data->map.east_texture)
		return (-1);
	while (str[y] && str[y] == ' ')
		y++;
	if (str[y] != 0)
		return (-5);
	return (0);
}
