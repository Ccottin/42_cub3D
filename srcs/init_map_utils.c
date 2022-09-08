/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 23:36:55 by ccottin           #+#    #+#             */
/*   Updated: 2022/09/07 23:38:59 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_cpy(t_data *data, char *buffer, int start, int end)
{
	int	i;

	data->map.map[data->map.map_size] = ft_calloc(end - start + 1);
	if (!data->map.map[data->map.map_size])
		return (-1);
	i = 0;
	while (buffer[start] && buffer[start] != '\n' && start < end)
	{
		data->map.map[data->map.map_size][i] = buffer[start];
		i++;
		start++;
	}
	data->map.map_size++;
	return (0);
}

char	*ft_concat(char *s1, char *s2, int end)
{
	char	*ret;
	int		i;
	int		y;

	if (!s1 || !s2)
		return (0);
	ret = ft_calloc(ft_strlen(s1) + end + 2);
	if (!ret)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	y = 0;
	while (y < end)
	{
		ret[i] = s2[y];
		i++;
		y++;
	}
	free(s1);
	return (ret);
}

int	check_last_char(t_data *data, char *buffer, int end)
{
	int	i;

	i = 0;
	while (data->map.map[data->map.map_size - 1][i])
		i++;
	if (i != 0 && data->map.map[data->map.map_size - 1][i - 1] == '\n')
		return (0);
	data->map.map[data->map.map_size - 1]
		= ft_concat(data->map.map[data->map.map_size - 1], buffer, end);
	if (!data->map.map[data->map.map_size - 1])
		return (-1);
	return (1);
}

int	get_map_size(char *av, char *buffer)
{
	int	ret;
	int	size;
	int	i;
	int	fd;

	fd = open(av, O_RDONLY);
	if (!fd || fd == -1 || read(fd, buffer, 0) == -1)
		return (-1);
	ret = 500;
	size = 0;
	while (ret == 500)
	{
		ret = read(fd, buffer, 500);
		i = 0;
		while (buffer[i])
		{
			if (buffer[i] == '\n')
				size++;
			buffer[i] = 0;
			i++;
		}
	}
	close(fd);
	return (size);
}

int	malloc_gm_init(t_data *data, char **buffer, char *av)
{
	int	m_size;

	*buffer = ft_calloc(501);
	if (!*buffer)
		return (-1);
	m_size = get_map_size(av, *buffer);
	if (m_size < 0)
	{
		free(*buffer);
		return (-1);
	}
	m_size++;
	data->map.map = ft_calloc((m_size + 2) * sizeof(char *));
	if (!data->map.map)
	{
		free(*buffer);
		return (-1);
	}
	return (0);
}
