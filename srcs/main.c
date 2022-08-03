#include "header.h"

int	main(int ac, char **av)
{
	t_data	data;
	int	ret;

	if (ac != 0)
		ft_return(1, &data);
	ret = init_map(av[1], &data);
	if (ret)
		ft_return(ret, &data);
	return (0);
}
