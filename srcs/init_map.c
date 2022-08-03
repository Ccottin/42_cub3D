/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:21:42 by ccottin           #+#    #+#             */
/*   Updated: 2022/08/03 18:04:48 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


//bon on s' est un peu perdue, l'idee c est de faire une fonction qui copie, et si lq ligne precedente est pas finie par un \n on la realloc et on copie dedans jusko \n, ca nous evitera de galerer avec la EOF
int	ft_cpy(t_data *data, char *buffer, int start, int end)
{
	int	i;

	if (data->map_size > 0 && start == 0)
	{
		i = 0;
		while (data->map[data->map_size - 1][i])
			i++;
		if (data->map[data->map_size - 1][i - 1] != '\n')
			data->
	}
	data->map[data->map_size] = ft_calloc(end - start + 1);
	if (!data->map[data->map_size])
		return (-1);
	i = 0;
	while (buffer[start] && buffer[start] != '\n')
	{
		data->map[data->map_size][i] = buffer[start];
		i++;
		start++;
	}
	return (0);
}

int	put_line(t_data *data, char *buffer)
{
	int	i;
	int	start;
//pense a trovuer la taille de ton map **;
	i = 0;
	start = i;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			ft_cpy(data, buffer, start, i);
			data->map_size++;
			start = i;
		}
		i++;
	}
	ft_cpy(data, buffer, start, i);
	return (0);
}

int	get_map(t_data *data, int fd)
{
	char	*buffer;
	int		ret;

	buffer = "";
	if (read(fd, buffer, 0) == -1)
		return (-1);
	buffer = ft_calloc(501);
	if (!buffer)
		return (-1);
	ret = 501;
	while (ret == 500)
	{
		ret = read(fd, buffer, 500);
		if (put_line(data, buffer))
			return (-1);
	}
	free(buffer);
	return (0);
}

int	init_map(char *av, t_data *data)
{
	int	i;
	int	fd;

	i = 0;
	while (av[i])
		i++;
	if (av[i - 4] != '.' || av[i - 3] != 'c' || av[i - 2] != 'u'
		|| av[i - 1] != 'b')
		return (-2);
	set_null(data);
	fd = open(av, O_RDONLY);
	if (!fd || fd == -1)
		return (-1);
	i = get_map(data, fd);
	if (i)
		return (i);
	close(fd);
	return (0);
}
