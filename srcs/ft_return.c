/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:18:16 by ccottin           #+#    #+#             */
/*   Updated: 2022/09/06 19:40:26 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_map(t_data *data)
{
	int	i;

	i = 0;
	if (!data->map.map)
		return;
	while (data->map.map[i])
	{
		free(data->map.map[i]);
		i++;
	}
	free(data->map.map);
}

void	clear_mlx(t_data *data)
{
	if (!data->win.mlx)
		return ;
	if (data->img0.img)
		mlx_destroy_image(data->win.mlx, data->img0.img);
	if (data->south.img)
		mlx_destroy_image(data->win.mlx, data->south.img);
	if (data->north.img)
		mlx_destroy_image(data->win.mlx, data->north.img);
	if (data->east.img)
		mlx_destroy_image(data->win.mlx, data->east.img);
	if (data->west.img)
		mlx_destroy_image(data->win.mlx, data->west.img);
	if (data->win.win)
	{
		mlx_loop_end(data->win.win);
		mlx_destroy_window(data->win.mlx, data->win.win);
	}
	if (data->win.mlx)
	{
		mlx_destroy_display(data->win.mlx);
		free(data->win.mlx);
	}
}

void	free_init(t_data *data)
{
	if (data->map.north_texture)
		free(data->map.north_texture);
	if (data->map.south_texture)
		free(data->map.south_texture);
	if (data->map.east_texture)
		free(data->map.east_texture);	
	if (data->map.west_texture)
		free(data->map.west_texture);
	data->map.north_texture = NULL;
	data->map.south_texture = NULL;
	data->map.east_texture = NULL;
	data->map.west_texture = NULL;
}

void	free_all(t_data *data)
{
	free_init(data);
	free_map(data);
	clear_mlx(data);
}

void	ft_return(int ret, t_data *data)
{
	if (ret == 1)
	{
		printf("Error\nPlease give a single map as argument\n");
		exit(0);
	}
	free_all(data);
	if (ret == -2)
	{
		printf("Error\nInvalid file extension\n");
		exit(0);
	}
	if (ret == -3)
	{
		printf("Error\nMap has a missing item\n");
		exit(0);
	}
	if (ret == -4)
	{
		printf("Error\nWrong identifier\n");
		exit(0);
	}
	if (ret == -5)
	{
		printf("Error\nToo many information for an element\n");
		exit(0);
	}
	if (ret == -6)
	{
		printf("Error\nColor range must be between 0 and 255\n");
		exit(0);
	}
	if (ret == -7)
	{
		printf("Error\nPlease check your informations again\n");
		exit(0);
	}
	if (ret == -8)
	{
		printf("Error\nToo few information for an element\n");
		exit(0);
	}
	if (ret == -9)
	{
		printf("Error\nInvalid map caracter\n");
		exit(0);
	}
	if (ret == -10)
	{
		printf("Error\nMap should have one starting position\n");
		exit(0);
	}
	if (ret == -11)
	{
		printf("Error\nMap is not surrounded by wall\n");
		exit(0);
	}
	if (ret == -1)
	{
		printf("Error\n");
		perror("cub3D ");
		exit (1);
	}
}
