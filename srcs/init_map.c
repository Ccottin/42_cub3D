#include "header.h"

int	init_map(char *av, t_data *data)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	if (av[i - 4] != '.' || av[i - 3] != 'c' || av[i - 2] != 'u'
		|| av[i - 1] != 'b')
		return (-2);
	set_null(data);
	i = open(av, O_RDONLY);
	if (!i || i == -1)
		return (-1);
}
