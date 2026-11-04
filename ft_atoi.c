/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:19:28 by sancuta           #+#    #+#             */
/*   Updated: 2026/11/04 18:34:37 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	is_invalid_val(const char *nptr, int res, size_t i, int sign)
{
	bool	is_invalid;

	is_invalid = (sign == 1 && res > ((INT_MAX - nptr[i] + 48) / 10))
		|| (sign == -1 && res < ((INT_MIN + nptr[i] - 48) / 10));
	if (is_invalid)
		errno = EINVAL;
	return (is_invalid);
}

/*	pay attention to the wording in strtol(3):
		"The  string  may  begin  with an arbitrary amount of
		white space (as determined by isspace(3)) followed by
		a single optional '+' or '-' sign.
	only **one** sign check is needed!*/

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
	if (ft_issign(nptr[i]))
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] && ft_isdigit(nptr[i]))
	{
		if (is_invalid_val(nptr, res, i, sign))
			return (0);
		res = res * 10 + sign * (nptr[i] - 48);
		i++;
	}
	return (res);
}
