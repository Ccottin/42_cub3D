#include "header.h"

int	main(void)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	if (!mlx)
		return (-1);
	win = mlx_new_window(mlx, 500, 500, "Hello World");
	if (!win)
		return (-1);
	mlx_loop(mlx);
	return (0);
}
