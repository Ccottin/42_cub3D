/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:21:42 by ccottin           #+#    #+#             */
/*   Updated: 2022/08/04 19:07:02 by ccottin          ###   ########.fr       */
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
	if (i == 0 || data->map.map[data->map.map_size - 1][i - 1] == '\n')
		return (0);
	data->map.map[data->map.map_size - 1]
		= ft_concat(data->map.map[data->map.map_size - 1], buffer, end);
	if (!data->map.map[data->map.map_size - 1])
		return (-1);
	return (1);
}

int	put_line_2(t_data *data, char *buffer, int start, int i)
{
	int	ret;

	ret = 0;
	if (data->map.map_size > 0 && start == 0)
		ret = check_last_char(data, buffer, i);
	if (ret == -1)
		return (-1);
	if (ret == 0)
	{
		if (ft_cpy(data, buffer, start, i))
			return (-1);
	}
	return (0);
}

int	put_line(t_data *data, char **buffer)
{
	int	i;
	int	start;

	i = 0;
	start = i;
	while ((*buffer)[i])
	{
		if ((*buffer)[i] == '\n')
		{
			if (put_line_2(data, *buffer, start, i))
				return (-1);
			start = i + 1;
		}
		i++;
	}
	if (ft_cpy(data, *buffer, start, i))
		return (-1);
	i = 0;
	while ((*buffer)[i])
		(*buffer)[i++] = 0;
	return (0);
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
	data->map.map = ft_calloc((m_size + 2) * sizeof(char *));
	if (!data->map.map)
	{
		free(*buffer);
		return (-1);
	}
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
/* Poutoi chef si tu veux le tester plusse :3 jpense que ca ira mais sait-on jamais, aussi jsuis pas sure 
d'avoir cree un fichier sans retour chariot ducu si t y arrives jveux bien que tu le tentes 
int	main(int ac, char **av)
{
	int	i;
	t_data data;

	(void)ac;
	i = init_map(av[1], &data);
	printf("return = %d, map size = %d\n", i, data.map_size);
	i = 0;
	while (data.map[i])
	{
		printf("1 = %s\n", data.map[i]);
		i++;
	}
	i = 0;
	while (data.map[i])
	{
		free(data.map[i]);
		i++;
	}
	free(data.map);
	return (0);
}*/
