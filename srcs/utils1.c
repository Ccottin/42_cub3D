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

char	*ft_strdup(char *s)
{
	char	*ret;
	size_t	i;

	ret = ft_calloc(ft_strlen(s)+ 1);
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

void	pixel_to_image(t_map *set, int x, int y, int color)
{
	char	*dst;

	dst = set->img.addr + (y * set->img.line_length + x * (set->img.bpx / 8));
	*(unsigned int*)dst = color;
}
