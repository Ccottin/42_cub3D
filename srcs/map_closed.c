/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_closed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 00:42:48 by ccottin           #+#    #+#             */
/*   Updated: 2022/09/08 00:43:52 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	find_it(char **map)
{
	int	ret;
	int	y;

	y = 0;
	ret = 0;
	while (map[y])
	{
		if (ret < ft_strlen(map[y]))
			ret = ft_strlen(map[y]);
		y++;
	}
	return (ret);
}

int	y_loop(char **map, int y, int x)
{
	if (map[y][x] == '1' && map[y + 1]
		&& ft_strlen(map[y + 1]) > x && (map[y + 1][x] == '0'
			|| is_char_acter(map[y + 1][x]) == 1))
	{
		while (map[y] && ft_strlen(map[y]) > x
			&& (is_char_map(map[y][x]) == 1
			|| is_char_acter(map[y][x]) == 1))
			y++;
		y--;
	}
	else if (map[y][x] == '0')
		return (-1);
	if (!map[y] || ft_strlen(map[y]) <= x || map[y][x] == '0'
		|| is_char_acter(map[y][x]) == 1)
	{
		return (-1);
	}
	y++;
	return (y);
}

int	check_all_y(char **map)
{
	int	x;
	int	y;
	int	bigger_line;

	x = 0;
	y = 0;
	bigger_line = find_it(map);
	while (map[y])
	{
		if (ft_strlen(map[y]) > x && map[y][x] != ' ')
		{
			y = y_loop(map, y, x);
			if (y == -1)
				return (-1);
		}
		else
			y++;
		if (!map[y] && x < bigger_line)
		{
			y = 0;
			x++;
		}
	}
	return (0);
}

int	check_all_x(char **map, int x, int y)
{
	while (map[y])
	{
		if (map[y][x] && map[y][x] == ' ')
		{
			while (map[y][x] && map[y][x] == ' ')
				x++;
		}
		else
		{
			if (map[y][x] == '0')
				return (-1);
			while (map[y][x] && (is_char_map(map[y][x]) == 1
				|| is_char_acter(map[y][x]) == 1))
				x++;
			if (x > 0 && map[y][x - 1] && map[y][x - 1] != '1')
				return (-1);
		}
		if (!map[y][x])
		{
			y++;
			x = 0;
		}
	}
	return (0);
}

int	map_closed(t_data *data)
{
	if (check_all_x(data->map.map, 0, 0))
		return (-11);
	if (check_all_y(data->map.map))
		return (-11);
	return (0);
}
