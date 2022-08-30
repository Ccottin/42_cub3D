#include "test.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	pixel_to_image(t_map *set, int x, int y, int color)
{
	char	*dst;
	
	dst = set->img.addr + (y * set->img.line_length + x * (set->img.bpx / 8));
	*(unsigned int*)dst = color;
}

char	*ft_strdup(const char *s)
{
	char	*ret;
	int	i;

	ret = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

void	*ft_calloc(int size)
{
	char	*ptr;
	int	i;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		ptr[i] = 0;
		i++;
	}
	return ((void*)ptr);
}

char	**map_init(void)
{
	char	**map;

	if (!(map = ft_calloc(sizeof(char*) * 6)))
		return (NULL);
	if (!(map[0] = ft_strdup("1111111111")))
		return (NULL);
	if (!(map[1] = ft_strdup("1000000001")))
		return (NULL);
	if (!(map[2] = ft_strdup("1000000001")))
		return (NULL);
	if (!(map[3] = ft_strdup("1000000001")))
		return (NULL);
	if (!(map[4] = ft_strdup("1111111111")))
		return (NULL);
	return (map);
}
