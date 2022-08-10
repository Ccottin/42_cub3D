#include "test.h"

char	*ft_strdup(const char *s)
{
	char	*ret;
	size_t	i;

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

void	*ft_calloc(size_t size)
{
	char	*ptr;
	int	i;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		prt[i] = 0;
		i++;
	}
	return ((void*)ptr);
}

char	**map_init(void)
{
	char	**map;

	if (!map = ft_calloc(sizeof(char*) * 6))
		return (NULL);
	if (!map[0] = ft_strdup("111111"))
		return (NULL);
	if (!map[1] = ft_strdup("10P001"))
		return (NULL);
	if (!map[2] = ft_strdup("100001"))
		return (NULL);
	if (!map[3] = ft_strdup("100001"))
		return (NULL);
	if (!map[4] = ft_strdup("111111"))
		return (NULL);
	return (map);
}

void	set_struct(t_map *set)
{
	set->player_x = 1;
	set->player_y = 2;
	set->dirx = -1;
	set->diry = 0;
	set->planex = 0;
	set->planey = 70;
	set->screen_l = 500;
	set->screen_w = 500;
	set->lengh_plane = (set->screen_l / 2) / tan(set->planey / 2);


}

int	main(void)
{
	void	*mlx;
	void	*win;
	char	**map;

	mlx = mlx_init();
	if (!mlx)
		return (-1);
	win = mlx_new_window(mlx, 500, 500, "Hello World");
	if (!win)
		return (-1);
	map = map_init();
	if (!map)
		return (-1);
	mlx_loop(mlx);
	return (0);
}
