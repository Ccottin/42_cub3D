#include "header.h"

int	get_new_map(t_data *data, int i)
{
	int	size;
	char	**new;

	size = i;
	while (data->map.map[size]
		&& is_char_map(data->map.map[size][0]))
		size++;
	new = ft_calloc(sizeof(char *) * (size - i + 1));
	if (!new)
		return (-1);
	size = 0;
	while (data->map.map[i]
		&& size < data->map.map_size)
	{
		new[size++] = ft_strdup2(data->map.map[i++], data->map.map_size);
		if (!new[size - 1])
			return (-1);
	}
	free_map(data);
	data->map.map = new;
	return (0);
}

void	player_pos(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map.map[y])
	{
		x = 0;
		while (data->map.map[y][x])
		{
			if (is_char_acter(data->map.map[y][x]))
			{
				data->map.player.player_x = x;
				data->map.player.player_y = y;
				data->map.player.player_facing
					= data->map.map[y][x];
				return ;
			}
			x++;
		}
		y++;
	}
}

int	check_all_y(char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y] && map[y][x])
	{
		while (map[y] && map[y][x] && map[y][x] == ' ')
			y++;
		if (map[y] && map[y][x] && map[y][x] != '1')
			return (-1);
		y++;
		while (map[y] && map[y][x] && (is_char_map(map[y][x]) == 1
			|| is_char_acter(map[y][x])))
		{
			y++;
		}
		if (map[y - 1] && map[y - 1][x] && map[y - 1][x] != '1')
			return (-1);
		x++;
		y = 0;
	}
	return (0);
}

int	check_all_x(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] && map[y][x] == ' ')
			x++;
		if (map[y][x] && map[y][x] != '1')
			return (-1);
		x++;
		while (map[y][x] && (is_char_map(map[y][x]) == 1
			|| is_char_acter(map[y][x])))
			x++;
		if (map[y][x - 1] && map[y][x - 1] != '1')
			return (-1);
		y++;
	}
	return (0);
}

int	map_closed(t_data *data)
{
	if (check_all_x(data->map.map))
		return (-11);
	printf("1\n");
	if (check_all_y(data->map.map))
		return (-11);
	printf("2\n");
	player_pos(data);
	return (0);
}

int	check_map(t_data *data)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (data->map.map[y])
	{
		x = 0;
		while (data->map.map[y][x] && (is_char_map(data->map.map[y][x])
			|| is_char_acter(data->map.map[y][x])))
		{
			if (is_char_acter(data->map.map[y][x]))
				count++;
			x++;
		}
		if (x != ft_strlen(data->map.map[y]))
			return (-9);
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
	if (get_new_map(data, i))
		return (-1);
	ret = check_map(data);
	if (ret)
		return (ret);
	if  (map_closed(data))
		return (-11);

	return (0);
}
