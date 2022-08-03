#include "header.h"

void	ft_return(int ret, t_data *data)
{
	if (ret == 1)
	{
		printf("Error\nPlease give a single map as argument\n");
		exit(0);
	}
	if (ret == -2)
	{
		printf("Error\nInvalid file extension\n");
		exit(0);
	}
	if (ret == -1)
	{
		printf("Error\n");
		perror("cub3D ");
		exit (1);
	}
}
