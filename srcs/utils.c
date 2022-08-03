/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:24:11 by ccottin           #+#    #+#             */
/*   Updated: 2022/08/03 17:26:41 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*ft_calloc(size_t nmem)
{
	char	*ret;
	size_t	i;

	ret = malloc(nmem);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < nmem)
	{
		ret[i] = 0;
		i++;
	}
	return ((void *)ret);
}
