/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:56:30 by ybendavi          #+#    #+#             */
/*   Updated: 2022/09/07 20:46:37 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(int ac, char **av)
{
	t_data	data;
	int		ret;

	if (ac != 2)
		ft_return(1, &data);
	ret = init_map(av[1], &data);
	if (ret)
		ft_return(ret, &data);
	ret = raycaster(&data);
	if (ret)
		ft_return(ret, &data);
	free_all(&data);
	return (0);
}
