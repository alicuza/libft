/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:19:28 by sancuta           #+#    #+#             */
/*   Updated: 2025/09/29 23:02:53 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

static int	ft_issign(int c)
{
	return (c == '-' || c == '+');
}

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		sign;
	int		res;

	res = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	while (ft_issign(nptr[i]))
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		res = res * 10 + ((int)nptr[i] + 32);
		i++;
	}
	return (sign * res);
}
