/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:21:42 by ccottin           #+#    #+#             */
/*   Updated: 2022/09/08 00:40:22 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	put_line_2(t_data *data, char *buffer, int *start, int *i)
{
	int	ret;

	*i = 0;
	*start = 0;
	while (buffer[*i])
	{
		if (buffer[*i] == '\n')
		{
			ret = 0;
			if (data->map.map_size > 0 && *start == 0)
			ret = check_last_char(data, buffer, *i);
			if (ret == -1)
				return (-1);
			if (ret == 0)
			{
				if (ft_cpy(data, buffer, *start, *i))
					return (-1);
			}
			*start = *i + 1;
		}
		(*i)++;
	}
	return (0);
}

int	put_line(t_data *data, char **buffer)
{
	int	i;
	int	start;

	if (put_line_2(data, *buffer, &start, &i))
		return (-1);
	if (start == 0 && i == 500)
	{
		data->map.map[data->map.map_size - 1]
			= ft_concat(data->map.map[data->map.map_size - 1],
				*buffer, i);
		if (!data->map.map[data->map.map_size - 1])
			return (-1);
	}
	else
	{
		if (ft_cpy(data, *buffer, start, i))
			return (-1);
	}
	i = 0;
	while ((*buffer)[i])
		(*buffer)[i++] = 0;
	return (0);
}

int	get_map(t_data *data, char *av)
{
	char	*buffer;
	int		ret;
	int		fd;

	if (malloc_gm_init(data, &buffer, av))
		return (-1);
	fd = open(av, O_RDONLY);
	if (!fd || fd == -1 || read(fd, buffer, 0) == -1)
	{
		free(buffer);
		return (-1);
	}
	ret = 500;
	while (ret == 500)
	{
		ret = read(fd, buffer, 500);
		if (put_line(data, &buffer))
		{
			free(buffer);
			return (-1);
		}
	}
	close(fd);
	free(buffer);
	return (0);
}

int	init_map(char *av, t_data *data)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	if (av[i - 4] != '.' || av[i - 3] != 'c' || av[i - 2] != 'u'
		|| av[i - 1] != 'b')
		return (-2);
	set_null(data);
	if (get_map(data, av))
		return (-1);
	i = set_info(data);
	if (i)
		return (i);
	return (0);
}
