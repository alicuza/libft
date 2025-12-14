/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:49:33 by sancuta           #+#    #+#             */
/*   Updated: 2025/12/13 16:12:02 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format_spec_handler(int flag, const char *s)
{
	if (flag == -1)
		return (-1);
	else if (flag)
	{
		format_data = get_form_spec(&s, g_valid_flags);
		if (format_data.conv_spec == -1)
			return (-1);
		return (print_arg(&format_data, &args));
	}
	else
		return (ft_putchar(*s++));
}
