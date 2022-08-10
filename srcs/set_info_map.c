#include "header.h"

/*petit erratum, j ai inverse les x et le y, du coup pour la structure et les cooronees sur perso j ai re echange les bails, 
en esperant aue ce ne soit pas trop confu*/

int	get_new_map(t_data *data, int i)
{
	int	size;
	char	**new;

	size = i;
	while (data->map.map[size]
		&& is_char_map(data->map.map[size][0]))
		size++;
	new = ft_calloc(sizeof(char *) * (size - i + 2));
	if (!new)
		return (-1);
	size = 0;
	while (data->map.map[i]
		&& size < data->map.map_size)
	{
		new[size++] = ft_strdup(data->map.map[i++]);
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
				data->map.player.player_y = x;
				data->map.player.player_x = y;
				data->map.player.player_facing
					= data->map.map[y][x];
				return ;
			}
			x++;
		}
		y++;
	}
}

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
			if (map[y][x] == '1' && ft_strlen(map[y + 1]) > x && map[y + 1][x] == '0')
			{
				while (map[y] && ft_strlen(map[y]) > x && (is_char_map(map[y][x]) == 1 || is_char_acter(map[y][x]) == 1))
					y++;
				y--;
			}
			else if (map[y][x] == '0')
				return (-1);
			if (!map[y] || ft_strlen(map[y]) <= x || map[y][x] == '0')
				return (-1);
			y++;
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

int	check_all_x(char **map)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (map[y])
	{
		while (map[y][x] == ' ')
			x++;
		if (x == '0')
			return (-1);
		while (map[y][x] && (is_char_map(map[y][x]) == 1 || is_char_acter(map[y][x]) == 1))
			x++;
		if (x > 0 && map[y][x - 1] && map[y][x - 1] != '1')
			return (-1);
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
	if (check_all_x(data->map.map))
		return (-11);
	if (check_all_y(data->map.map))
		return (-11);
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
	while (y < data->map.map_size && data->map.map[y])
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
