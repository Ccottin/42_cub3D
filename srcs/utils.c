/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:24:11 by ccottin           #+#    #+#             */
/*   Updated: 2022/08/04 22:16:33 by ccottin          ###   ########.fr       */
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

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	is_char_acter(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

int	is_char_map(char c)
{
	if (c == '1' || c == '0')
		return (1);
	if (c == ' ')
		return (2);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((nptr[i] > 8 && nptr[i] < 14) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (nptr[i] > 47 && nptr[i] < 58)
	{
		res = res * 10 + (nptr[i] - 48);
		i++;
	}
	return (res * sign);
}
