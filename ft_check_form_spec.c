/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_form_spec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 14:18:51 by sancuta           #+#    #+#             */
/*   Updated: 2025/12/14 04:34:45 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_form_spec(const char **s)
{
	int	written;

	if (**s == '%')
	{
		(*s)++;
		if (!(**s))
			return (-1);
		if (**s == '%')
		{
			written = ft_putchar(**s);
			if (written < 0)
				return (-1);
			(*s)++;
		}
		return (1);
	}
	return (0);
}
