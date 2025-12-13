/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_precision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 23:52:35 by sancuta           #+#    #+#             */
/*   Updated: 2025/12/14 00:00:29 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_get_precision(const char **s, const char *mask_set)
{
	int	precision;

	precision = 0;
	if (**s == '.')
	{
		(*s)++;
		precision = get_number(s);
	}
	return (precision);
}
