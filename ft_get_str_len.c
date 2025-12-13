/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_str_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:42:09 by sancuta           #+#    #+#             */
/*   Updated: 2025/12/13 15:44:31 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_get_str_len(t_format_specifier *data, char *s)
{
	int	len;

	if (!s)
	{
		s = "(null)";
		data->precision = 0;
	}
	len = ft_strlen(s);
	if ((data->flag & FLAG_DOT) && (data->precision != -1) && (len > data->precision))
		len = data->precision;
	return (len);
}
