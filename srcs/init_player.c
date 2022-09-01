#include "header.h"

int	init_player(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (data->map.map[y] && !is_char_acter(data->map.map[y][x]))
	{
		x = 0;
		while (data->map.map[y][x] && !is_char_acter(data->map.map[y][x]))
			x++;
		if (!is_char_acter(data->map.map[y][x]))
			y++;
	}
	

