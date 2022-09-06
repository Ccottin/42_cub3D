#include "header.h"

void	set_other_dir(t_data *data, char player_dir)
{
	if (player_dir == 'E')
	{
		data->caster.dirplayerx = 1;
		data->caster.dirplayery = 0;
		data->caster.planex = 0;
		data->caster.planey = 0.6;
	}
	if (player_dir == 'W')
	{
		data->caster.dirplayerx = -1;
		data->caster.dirplayery = 0;
		data->caster.planex = 0;
		data->caster.planey = 0.6;
	}
}

void	set_dir(t_data *data, char player_dir)
{
	if (player_dir == 'N')
	{
		data->caster.dirplayerx = 0;
		data->caster.dirplayery = -1;
		data->caster.planex = 0.6;
		data->caster.planey = 0;
	}
	else if (player_dir == 'S')
	{
		data->caster.dirplayerx = 0;
		data->caster.dirplayery = 1;
		data->caster.planex = 0.6;
		data->caster.planey = 0;
	}
	else
		set_other_dir(data, player_dir);
}

void	init_player(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (data->map.map[y]	&& !is_char_acter(data->map.map[y][x]))
	{
		while (data->map.map[y][x] && !is_char_acter(data->map.map[y][x]))
			x++;
		if (!is_char_acter(data->map.map[y][x]))
		{
			x = 0;
			y++;
		}
	}
	data->caster.playerx = x + 0.5;
	data->caster.playery = y + 0.5;
	set_dir(data, data->map.map[y][x]);
	data->map.map[y][x] = '0';
}
