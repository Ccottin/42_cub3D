#include "header.h"

int	key_right(t_data *data)
{
	(void)data;
	return (0);
}

int	key_left(t_data *data)
{
	(void)data;
	return (0);
}

int	move_forward(t_data *data)
{
	data->caster.playerx = data->caster.playerx + data->caster.dirplayerx;
	data->caster.playery = data->caster.playery + data->caster.dirplayery;
	return (0);
}

int	move_left(t_data *data)
{
	(void)data;
	return (0);
}

int	move_right(t_data *data)
{
	(void)data;
	return (0);
}

int	move_backward(t_data *data)
{
	data->caster.playerx = data->caster.playerx - data->caster.dirplayerx;
	data->caster.playery = data->caster.playery - data->caster.dirplayery;
	(void)data;
	return (0);
}
