#include "header.h"

void	ft_SHOW_US_WHAT_YOU_GOT(t_data *data)
{
	int	i;

	i = 0;
	while (data->map.map[i])
	{
//		printf("%s\n", data->map.map[i]);
		i++;
	}
//	printf("\n\nN = %s\nS = %s\nE = %s\nW = %s\n\n", data->map.north_texture, data->map.south_texture, data->map.east_texture, data->map.west_texture);
//	printf("Floor\nred = %d\ngreen = %d\nblue = %d\n", data->map.floor_color.red, data->map.floor_color.green, data->map.floor_color.blue);
//	printf("Ceiling\nred = %d\ngreen = %d\nblue = %d\n", data->map.ceiling_color.red, data->map.ceiling_color.green, data->map.ceiling_color.blue);
 
}

int	main(int ac, char **av)
{
	t_data	data;
	int	ret;

	if (ac != 2)
		ft_return(1, &data);
	ret = init_map(av[1], &data);
//	printf("ret = %d\n", ret);
	ft_SHOW_US_WHAT_YOU_GOT(&data);
	if (ret)
		ft_return(ret, &data);
	ret = raycaster(&dta);
	if (ret)
		ft_return(ret, &data);
	free_all(&data);
	return (0);
}
