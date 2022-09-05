#include "header.h"

int	keyboard(int keycode, t_data *data)
{
	if (keycode == 65361)
		return (key_left(data));
	else if (keycode == 65363)
		return (key_right(data));
	else if (keycode == 119)
		return (move_forward(data));
	else if (keycode == 97)
		return (move_left(data));
	else if (keycode == 100)
		return (move_right(data));
	else if (keycode == 115)
		return (move_backward(data));
	else if (keycode == 65307)
	{
		free_all(data);
		exit(0);
	}
	return (0);
}

int	close_cross(t_data *data)
{
	free_all(data);
	exit(0);
}

int	events_handler(t_data *data)
{
	mlx_hook(data->win.win, 2, 1L << 0, keyboard, data);
	mlx_hook(data->win.win, 17, 0L, close_cross, data);
	return (0);
}
