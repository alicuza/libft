/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 23:45:27 by sancuta           #+#    #+#             */
/*   Updated: 2025/12/13 23:55:48 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_get_flags(const char **s, const char *mask_set)
{
	int				i;
	unsigned int	flag;

	flag = 0;
	i = ft_indchr(mask_set, **s);
	while (i != -1)
	{
		flag |= (1 << i);
		(*s)++;
		i = ft_indchr(mask_set, **s);
	}
	return (flag);
}
