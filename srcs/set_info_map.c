/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_info_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:16:33 by ybendavi          #+#    #+#             */
/*   Updated: 2022/09/08 00:43:18 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	get_new_map(t_data *data, int i)
{
	int		size;
	char	**new;

	size = i;
	while (data->map.map[size]
		&& is_char_map(data->map.map[size][0]))
		size++;
	new = ft_calloc(sizeof(char *) * (size - i + 3));
	if (!new)
		return (-1);
	size = 0;
	while (data->map.map[i]
		&& is_char_map(data->map.map[i][0]))
	{
		new[size++] = ft_strdup(data->map.map[i++]);
		if (!new[size - 1])
			return (-1);
	}
	free_map(data);
	data->map.map = new;
	return (0);
}

int	check_map(t_data *data, int i)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < data->map.map_size && data->map.map[i])
	{
		x = 0;
		while (data->map.map[i][x] && (is_char_map(data->map.map[i][x])
			|| is_char_acter(data->map.map[i][x])))
		{
			if (is_char_acter(data->map.map[i][x]))
				count++;
			x++;
		}
		if (x != ft_strlen(data->map.map[i]))
			return (-9);
		i++;
		y++;
	}
	if (count != 1)
		return (-10);
	return (0);
}

void	get_value_map(t_data *data, int i)
{
	int	x;
	int	y;

	y = i;
	while (data->map.map[y])
	{
		x = 0;
		while (data->map.map[y][x])
			x++;
		if (x > data->map.map_width)
			data->map.map_width = x;
		y++;
	}
	data->map.map_size = y - i;
}

int	detach_map(t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	while (data->map.map[i]
		&& !is_char_map(data->map.map[i][0]))
		i++;
	get_value_map(data, i);
	ret = check_map(data, i);
	if (ret)
		return (ret);
	if (get_new_map(data, i))
		return (-1);
	if (map_closed(data))
		return (-11);
	return (0);
}
