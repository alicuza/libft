/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:55:17 by sancuta           #+#    #+#             */
/*   Updated: 2025/12/13 16:05:21 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char	g_valid_flags[] = "-0#+ ";

const char	g_valid_conv_spec[] = "csdiupxX";

const int	g_allowed_flags[] = {
	FLAG_MINUS,
	FLAG_MINUS | FLAG_DOT,
	FLAG_MINUS | FLAG_ZERO | FLAG_PLUS | FLAG_SPACE | FLAG_DOT,
	FLAG_MINUS | FLAG_ZERO | FLAG_PLUS | FLAG_SPACE | FLAG_DOT,
	FLAG_MINUS | FLAG_ZERO | FLAG_DOT,
	FLAG_MINUS,
	FLAG_MINUS | FLAG_ZERO | FLAG_HASH | FLAG_DOT,
	FLAG_MINUS | FLAG_ZERO | FLAG_HASH | FLAG_DOT
};

int	ft_printf(const char *s, ...)
{
	size_t				res;
	int					cnt;
	va_list				args;
	t_format_specifier	format_data;

	if (!s)
		return (-1);
	va_start(args, s);
	res = 0;
	while (*s)
	{
		cnt = ft_format_spec_handler(check_format_specifier(s));
		if (cnt < 0)
			retun (-1);
		res += cnt;
	}
	return (res);
}

//TODO make 1 function for each struct member
t_format_specifier	get_format_specifier(const char **s, const char *mask_set)
{
	int					i;
	t_format_specifier	res;

	res = (t_format_specifier){0};
	res.precision = -1;
	i = ft_indchr(mask_set, **s);
	while (i != -1)
	{
		res.flag |= (1 << i);
		(*s)++;
		i = ft_indchr(mask_set, **s);
	}
	res.field_width = get_number(s);
	if (**s == '.')
	{
		res.flag = (res.flag | FLAG_DOT) & ~FLAG_ZERO;
		(*s)++;
		res.precision = get_number(s);
	}
	if (ft_indchr(g_valid_conv_spec, **s) != -1)
	{
		res.conv_spec = **s;
		res.flag &= g_allowed_flags[ft_indchr(g_valid_conv_spec,
				res.conv_spec)];
		(*s)++;
	}
	else
		res.conv_spec = -1;
	return (res);
}

int	get_number(const char **s)
{
	int	ret;

	ret = 0;
	while (ft_isdigit(**s))
	{
		ret *= 10;
		ret += **s - 48;
		(*s)++;
	}
	return (ret);
}

int	print_arg(t_format_specifier *data, va_list *args)
{
	int	ret;

	ret = 0;
	if (data->conv_spec == 'c')
		ret = print_char(data, va_arg(*args, int));
	else if (data->conv_spec == 's')
		ret = print_str(data, va_arg(*args, char *));
	else if (data->conv_spec == 'p')
		ret = print_ptr(data, (unsigned long)va_arg(*args, void *));
	else if (data->conv_spec == 'd' || data->conv_spec == 'i')
		ret = print_int(data, va_arg(*args, int));
	else if (data->conv_spec == 'u')
		ret = print_uint(data, va_arg(*args, unsigned int));
	else if (data->conv_spec == 'x')
		ret = print_hex(data, va_arg(*args, unsigned int), "0123456789abcdef");
	else if (data->conv_spec == 'X')
		ret = print_hex(data, va_arg(*args, unsigned int), "0123456789ABCDEF");
	return (ret);
}

int	print_char(t_format_specifier *data, int c)
{
	int	ret;
	int	written;

	ret = 0;
	if (!(data->flag & FLAG_MINUS))
	{
		written = put_space(data, 1, 0);
		if (written < 0)
			return (-1);
		ret += written;
	}
	written = write(1, &c, 1);
	if (written < 0)
		return (-1);
	ret += written;
	if (data->flag & FLAG_MINUS)
	{
		written = put_space(data, 1, 0);
		if (written < 0)
			return (-1);
		ret += written;
	}
	return (ret);
}

/*
	How would a buffer work here? I could fill it from the back
	with spaces, then zeros and the sign, then the digits.
	Problem: there is no way to know what size it should be beforehand.
	So either I have a standard big buffer (maybe on the stack),
	or I malloc and realloc to the necessary size to write every
	successive element into the buffer, if it is too small.
 */

int	print_str(t_format_specifier *data, char *s)
{
	int	len;
	int	ret;
	int	written;

	ret = 0;
	len = ft_get_str_len(data, s);
	if (!(data->flag & FLAG_MINUS))
	{
		written = put_space(data, len, 0);
		if (written < 0)
			return (-1);
		ret += written;
	}
	written = write(1, s, len);
	if (written < 0)
		return (-1);
	ret += written;
	if (data->flag & FLAG_MINUS)
	{
		written = put_space(data, len, 0);
		if (written < 0)
			return (-1);
		ret += written;
	}
	return (ret);
}

int	abs_nbr_len(unsigned long n, unsigned long base)
{
	int	i;

	if (!n)
		return (1);
	i = 0;
	while (n)
	{
		n /= base;
		i++;
	}
	return (i);
}
