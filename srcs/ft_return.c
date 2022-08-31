/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:18:16 by ccottin           #+#    #+#             */
/*   Updated: 2022/08/31 16:23:08 by ybendavi         ###   ########.fr       */
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

void	free_all(t_data *data)
{
	free_map(data);
	if (data->map.north_texture)
		free(data->map.north_texture);
	if (data->map.south_texture)
		free(data->map.south_texture);
	if (data->map.east_texture)
		free(data->map.east_texture);	
	if (data->map.west_texture)
		free(data->map.west_texture);

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
