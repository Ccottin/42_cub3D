#include "header.h"

int	all_info_set(t_data *data)
{
	if (data->map.north_texture == NULL
		|| data->map.south_texture == NULL
		|| data->map.east_texture == NULL
		|| data->map.west_texture == NULL
		|| data->map.floor_color.red == -1
		|| data->map.floor_color.green == -1
		|| data->map.floor_color.blue == -1
		|| data->map.ceiling_color.red == -1 
		|| data->map.ceiling_color.green == -1
		|| data->map.ceiling_color.blue == -1)
		return (0);
	return (1);
}

char	*ft_strdup2(char *s, int size)
{
	char	*ret;
	size_t	i;

	ret = ft_calloc(size + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ret[i] = s[i];
		i++;
	}
	return (ret);
}