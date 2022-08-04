/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:15:16 by ccottin           #+#    #+#             */
/*   Updated: 2022/08/04 22:23:49 by ccottin          ###   ########.fr       */
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
		data->ceiling_color.red = r;
	else if (c == 'C' && *count == 1)
		data->ceiling_color.green = r;
	else if (c == 'C' && *count == 2)
		data->ceiling_color.blue = r;
	else if (c == 'F' && *count == 0)
		data->floor_color.red = r;
	else if (c == 'F' && *count == 1)
		data->floor_color.green = r;
	else if (c == 'F' && *count == 2)
		data->floor_color.blue = r;
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
	while  (y < 3 && str[*i] && (str[*i] >= '0' && str[*i] <= '9'))
		buffer[y++] = str[(*i)++];
	if (str[(*i)] && *count != 2 && str[(*i)] != ',')
	{
		free(buffer);
		return (-7);
	}
	(*i)++;
	ret = fill_colors(data, buffer, count, data->c);
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
	data->c = c;
	while (str[i] && count < 3)
	{
		ret = get_colors_2(data, str, &i, &count);
		if (ret)
			return (ret);
	}
	while (str[i] && str[i] == ' ')
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
	else
		return (-4);
	return (0);
}

int	set_info(t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	while (data->map[i] && !(is_char_map(data->map[i][0])))
	{
		printf("is char map = %d\n", is_char_map(data->map[i][0]));
		//BAWI JAMIE ya un tab sur ta premiere ligne omfg c'est pas autorise en plusse
		ret = search_info(data, data->map[i]);
		printf("%s, ret = %d\n", data->map[i], ret);
		if (ret)
			return (ret);
		i++;
	}
	if (data->north_texture == NULL || data->south_texture == NULL
		|| data->east_texture == NULL || data->west_texture == NULL
		|| data->floor_color.red == -1 || data->floor_color.green == -1
		|| data->floor_color.blue == -1 || data->ceiling_color.red == -1 
		|| data->ceiling_color.green == -1
		|| data->ceiling_color.blue == -1)
		return (-3);
	return (0);
}
