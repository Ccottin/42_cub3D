#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <mlx.h>

typedef struct s_win {
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	}	t_win;

typedef struct s_data {
	}	t_data;

void	ft_return(int ret, t_data *data);
void	set_null(t_data *data);

#endif
