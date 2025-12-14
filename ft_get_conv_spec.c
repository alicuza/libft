/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_conv_spec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:01:26 by sancuta           #+#    #+#             */
/*   Updated: 2025/12/14 00:31:23 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_get_conv_spec(const char **s, const char *mask_set)
{
	int	conv_spec;

	if (ft_indchr(g_valid_conv_spec, **s) != -1)
	{
		conv_spec = **s;
		(*s)++;
	}
	else
		conv_spec = -1;
	return (conv_spec);
}
