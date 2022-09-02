#include "header.h"

int	key_right(t_data *data)
{
	double	x;
	double	planx;

	x = data->caster.dirplayerx;
	planx = data->caster.planex;
	data->caster.dirplayerx = data->caster.dirplayerx * cos(0.15) - data->caster.dirplayery * sin(0.15);
	data->caster.dirplayery = x * sin(0.15) + data->caster.dirplayery * cos(0.15);
	data->caster.planex = data->caster.planex * cos(0.15) - data->caster.planey * sin(0.15);
	data->caster.planey = planx * sin(0.15) + data->caster.planey * cos(0.15);
	mlx_destroy_image(data->win.mlx, data->img0.img);
	if (get_img(data))
		return (-1);
	mlx_put_image_to_window(data->win.mlx, data->win.win, data->img0.img, 0, 0);
	return (0);
}

int	key_left(t_data *data)
{
	double	x;
	double	planx;

	x = data->caster.dirplayerx;
	planx = data->caster.planex;
	data->caster.dirplayerx = data->caster.dirplayerx * cos(-0.15) - data->caster.dirplayery * sin(-0.15);
	data->caster.dirplayery = x * sin(-0.15) + data->caster.dirplayery * cos(-0.15);
	data->caster.planex = data->caster.planex * cos(-0.15) - data->caster.planey * sin(-0.15);
	data->caster.planey = planx * sin(-0.15) + data->caster.planey * cos(-0.15);
	mlx_destroy_image(data->win.mlx, data->img0.img);
	if (get_img(data))
		return (-1);
	mlx_put_image_to_window(data->win.mlx, data->win.win, data->img0.img, 0, 0);
	return (0);
}

int	move_forward(t_data *data)
{
	double	mspeed;
	int	x_next;
	int	y_next;

	mspeed = 0.2;
	x_next = data->caster.playerx + data->caster.dirplayerx * mspeed;
	y_next = data->caster.playery + data->caster.dirplayery * mspeed;
	if (data->map.map[y_next][x_next] == '0')
	{
		data->caster.playerx = data->caster.playerx + data->caster.dirplayerx * mspeed;
		data->caster.playery = data->caster.playery + data->caster.dirplayery * mspeed;
		mlx_destroy_image(data->win.mlx, data->img0.img);
		if (get_img(data))
			return (-1);
		mlx_put_image_to_window(data->win.mlx, data->win.win, data->img0.img, 0, 0);
	}
	return (0);
}

int	move_left(t_data *data)
{
	double	mspeed;
	int	x_next;
	int	y_next;

	mspeed = 0.2;
	x_next = data->caster.playerx + data->caster.dirplayery * mspeed;
	y_next = data->caster.playery - data->caster.dirplayerx * mspeed;
	if (data->map.map[y_next][x_next] == '0')
	{
		data->caster.playerx = data->caster.playerx + data->caster.dirplayery * mspeed;
		data->caster.playery = data->caster.playery - data->caster.dirplayerx * mspeed;
		mlx_destroy_image(data->win.mlx, data->img0.img);
		if (get_img(data))
			return (-1);
		mlx_put_image_to_window(data->win.mlx, data->win.win, data->img0.img, 0, 0);
	}
	return (0);
}

int	move_right(t_data *data)
{
	double	mspeed;
	int	x_next;
	int	y_next;

	mspeed = 0.2;
	x_next = data->caster.playerx - data->caster.dirplayery * mspeed;
	y_next = data->caster.playery + data->caster.dirplayerx * mspeed;
	if (data->map.map[y_next][x_next] == '0')
	{
		data->caster.playerx = data->caster.playerx - data->caster.dirplayery * mspeed;
		data->caster.playery = data->caster.playery + data->caster.dirplayerx * mspeed;
		mlx_destroy_image(data->win.mlx, data->img0.img);
		if (get_img(data))
			return (-1);
		mlx_put_image_to_window(data->win.mlx, data->win.win, data->img0.img, 0, 0);
	}
	return (0);
}

int	move_backward(t_data *data)
{
	double	mspeed;
	int	x_next;
	int	y_next;

	mspeed = 0.2;
	x_next = data->caster.playerx - data->caster.dirplayerx * mspeed;
	y_next = data->caster.playery - data->caster.dirplayery * mspeed;
	if (data->map.map[y_next][x_next] == '0')
	{
		data->caster.playerx = data->caster.playerx - data->caster.dirplayerx * mspeed;
		data->caster.playery = data->caster.playery - data->caster.dirplayery * mspeed;
		mlx_destroy_image(data->win.mlx, data->img0.img);
		if (get_img(data))
			return (-1);
		mlx_put_image_to_window(data->win.mlx, data->win.win, data->img0.img, 0, 0);
	}
	return (0);
}
