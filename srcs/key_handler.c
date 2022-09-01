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
	mlx_destroy_image(data->win.mlx, data->img0.img);
	set_caster(data);
	if (get_img(data))
		return (-1);
	mlx_put_image_to_window(data->win.mlx, data->win.win, data->img0.img, 0, 0);
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
