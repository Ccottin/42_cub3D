#include "header.h"

void	ft_SHOW_US_WHAT_YOU_GOT(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[i])
	{
		printf("%s\n", data->map[i]);
		i++;
	}
	printf("\n\nN = %s\nS = %s\nE = %s\nW = %s\n\n", data->north_texture, data->south_texture, data->east_texture, data->west_texture);
	printf("Floor\nred = %d\ngreen = %d\nblue = %d\n", data->floor_color.red, data->floor_color.green, data->floor_color.blue);
	printf("Ceiling\nred = %d\ngreen = %d\nblue = %d\n", data->ceiling_color.red, data->ceiling_color.green, data->ceiling_color.blue);
 
}

int	main(int ac, char **av)
{
	t_data	data;
	int	ret;

	if (ac != 2)
		ft_return(1, &data);
	ret = init_map(av[1], &data);
	ft_SHOW_US_WHAT_YOU_GOT(&data);
	if (ret)
		ft_return(ret, &data);
	return (0);
}
