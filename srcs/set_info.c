/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:15:16 by ccottin           #+#    #+#             */
/*   Updated: 2022/09/06 18:00:02 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	fill_colors(t_data *data, char *buffer, int *count, char c)
{
	int	r;

	r = ft_atoi(buffer);
	if (r > 255)
		return (-6);
	if (c == 'C' && *count == 0)
		data->map.ceiling_color.red = r;
	else if (c == 'C' && *count == 1)
		data->map.ceiling_color.green = r;
	else if (c == 'C' && *count == 2)
		data->map.ceiling_color.blue = r;
	else if (c == 'F' && *count == 0)
		data->map.floor_color.red = r;
	else if (c == 'F' && *count == 1)
		data->map.floor_color.green = r;
	else if (c == 'F' && *count == 2)
		data->map.floor_color.blue = r;
	(*count)++;
	return (0);
}

int	get_colors_2(t_data *data, char *str, int *i, int *count)
{
	char	*buffer;
	int		y;
	int		ret;

	buffer = ft_calloc(4);
	if (!buffer)
		return (-1);
	y = 0;
	while (y < 3 && str[*i] && (str[*i] >= '0' && str[*i] <= '9'))
		buffer[y++] = str[(*i)++];
	if (str[(*i)] && *count != 2 && str[(*i)] != ',')
	{
		free(buffer);
		return (-7);
	}
	(*i)++;
	ret = fill_colors(data, buffer, count, data->map.c);
	free(buffer);
	if (ret)
		return (ret);
	return (0);
}

int	get_colors(t_data *data, char *str, int i, char c)
{
	int	count;
	int	ret;

	count = 0;
	while (str[i] && str[i] == ' ')
		i++;
	data->map.c = c;
	while (count < 3 && str[i])
	{
		ret = get_colors_2(data, str, &i, &count);
		if (ret)
			return (ret);
	}
	while (count < 3 && str[i] && str[i] == ' ')
		i++;
	if (str[i - 1] && str[i - 1] != '\n')
		return (-5);
	if (count != 3)
		return (-8);
	return (0);
}

int	search_info(t_data *data, char *str)
{
	if (is_char_acter(str[0]))
	{
		if (str[0] == 'N' && str[1] == 'O')
			return (get_info_wall_0(data, str, 2, 'N'));
		else if (str[0] == 'S' && str[1] == 'O')
			return (get_info_wall_0(data, str, 2, 'S'));
		else if (str[0] == 'E' && str[1] == 'A')
			return (get_info_wall_1(data, str, 2, 'E'));
		else if (str[0] == 'W' && str[1] == 'E')
			return (get_info_wall_1(data, str, 2, 'W'));
	}
	else if (str[0] == 'C' || str[0] == 'F')
		return (get_colors(data, str, 1, str[0]));
	else if (str[0] == 0)
		return (0);
	else
		return (-4);
	return (0);
}

int	set_info(t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	while (data->map.map[i] && !(is_char_map(data->map.map[i][0])))
	{
		ret = search_info(data, data->map.map[i]);
		if (ret)
			return (ret);
		i++;
	}
	if (data->map.map[i] && !(is_char_map(data->map.map[i][0]))
		&& !(is_char_acter(data->map.map[i][0])))
		return (-9);
	if (!all_info_set(data))
		return (-3);
	ret = detach_map(data);
	if (ret)
		return (ret);
	return (0);
}
