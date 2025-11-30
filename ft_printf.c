/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:55:17 by sancuta           #+#    #+#             */
/*   Updated: 2025/11/30 20:43:07 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
//#include <stdio.h>

const char	g_valid_conv_spec[] = "csdiupxX";

const int	g_allowed_flags[] =
{
	FLAG_MINUS,
	FLAG_MINUS | FLAG_DOT,
	FLAG_MINUS | FLAG_ZERO | FLAG_PLUS | FLAG_SPACE | FLAG_DOT,
	FLAG_MINUS | FLAG_ZERO | FLAG_PLUS | FLAG_SPACE | FLAG_DOT,
	FLAG_MINUS | FLAG_ZERO | FLAG_DOT,
	FLAG_MINUS,
	FLAG_MINUS | FLAG_ZERO | FLAG_HASH | FLAG_DOT,
	FLAG_MINUS | FLAG_ZERO | FLAG_HASH | FLAG_DOT,
};

int	ft_printf(const char *s, ...)
{
	size_t				res;
	size_t				cnt;
	va_list				args;
	t_format_specifier	format_data;

	if (!s)
		return (-1);
	va_start(args, s);
	res = 0;
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			if (!(*s))
				return (-1);
			if (*s == '%')
			{
				ft_putchar(*s);
				s++;
				res++;
				continue ;
			}
			format_data = get_format_specifier(&s, "-0#+ ");
//			printf("%u, %u, %u, %u\n", format_data.field_width, format_data.precision, format_data.flag, format_data.conv_spec);
			cnt = print_arg(&format_data, &args);
			if (cnt == -1)
				return (-1);
			res += cnt;
		}
		else
		{
			res += ft_putchar(*s);
			s++;
		}
	}
	return (res);
}

t_format_specifier	get_format_specifier(const char **s, const char *mask_set)
{
	int					i;
	t_format_specifier	res;

	res = (t_format_specifier){0};
	i = get_mask_index(**s, mask_set);
	while (i != -1)
	{
		res.flag |= (1 << i);
		(*s)++;
		i = get_mask_index(**s, mask_set);
	}
	res.field_width = get_number(s);
	if (**s == '.')
	{
		res.flag = (res.flag | FLAG_DOT) & ~FLAG_ZERO;
		(*s)++;
		res.precision = get_number(s);
	}
	res.conv_spec = **s;
	res.flag &= g_allowed_flags[ft_indchr(g_valid_conv_spec, res.conv_spec)];
	(*s)++;
	return (res);
}

int	get_mask_index(int c, const char *mask_set)
{
	int	i;

	i = 0;
	while (mask_set[i])
	{
		if (c == mask_set[i])
			return (i);
		i++;
	}
	return (-1);
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
	int		ret;

	ret = 0;
	if (data->conv_spec == 'c')
		ret = print_char(data, va_arg(*args, int));
	else if (data->conv_spec == 's')
		ret = print_str(data, va_arg(*args, char *));
	else if (data->conv_spec == 'p')
	{
		data->flag |= FLAG_HASH;
		ret = print_hex(data, (unsigned long)va_arg(*args, void *), "0123456789abcdef");
	}
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

	ret = 0;
	if (!(data->flag & FLAG_MINUS))
		ret += put_space(data, 1, 0);
	ret += write(1, &c, 1);
	if (data->flag & FLAG_MINUS)
		ret += put_space(data, 1, 0);
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
	size_t len;
	int ret;

	ret = 0;
	if ((data->flag & FLAG_DOT))
		len = data->precision;
	else
		len = ft_strlen(s);
	if (!(data->flag & FLAG_MINUS))
		ret += put_space(data, len, 0);
	ret += write(1, s, len);
	if (data->flag & FLAG_MINUS)
		ret += put_space(data, len, 0);
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

/*
int	print_uint(t_format_specifier data, unsigned int x, const char *base)
{
	char	*sign;
	char	*x_b;
	size_t	arg_len;

	if (!strcmp(base, "0123456789"))
		x_b = ft_itoa_base(x, base); // maybe include the sign into this function.
	arg_len = ft_strlen(x_b);
	sign = "";
	if (data.flag & FLAG_HASH)
	{
		arg_len += 2;
		sign = "0x";
	}
	if (data.field_width > arg_len)
	{
		if (data.flag & FLAG_MINUS)
		{
			write(1, sign, 2);
			write(1, x_b, arg_len);
			if(!add_padding(data.field_width - arg_len, ' '))
				return (-1);
		}
		if(!add_padding(data.field_width - arg_len, ' '))
			return (-1);
		write(1, sign, 2);
		write(1, x_b, arg_len);
		return (data.field_width);
	}
	else
	{
		write(1, sign, 2);
		write(1, x_b, arg_len);
	}
	return (arg_len);
}

int	print_int(t_format_specifier data, int n)
{
	char	sign;
	int		nbr_len;
	int		arg_len;

	nbr_len = abs_nbr_len(n);
	if (n < 0)
	{
		data.flags |= FLAG_NEG;
		arg_len++;
		sign = "-";
	}
	if (has_sign(data.flags))
	
}

int	has_sign()

	if (n < 0)
		data.flags |= FLAG_NEG;
	nbr_len = abs_nbr_len(n);
	arg_len = nbr_len;
	if (arg_len < data.precision)
		arg_len = data.precision;
	if (data.field_width > arg_len)
	{
		if (data.flag & FLAG_ZERO & ~FLAG_DOT)
			pad = '0';
		if (data.flag & FLAG_SPACE)
			pad = ' ';
		if (data.flag & FLAG_MINUS)
		{
			if(!add_padding(arg_len - nbr_len, '0'))
				return (-1);
			write(1, args, nbr_len);
			if(!add_padding(data.field_width - arg_len, pad))
				return (-1);
		}
		if(!add_padding(data.field_width - arg_len, pad))
			return (-1);
		if(!add_padding(arg_len - nbr_len, '0'))
			return (-1);
		write(1, args, nbr_len);
		return (data.field_width);
	}
	else
		write(1, args, arg_len);
	return (arg_len);
}
*/

/*
char	*convert_base(va_list args, )
{
	
}

		think about whether it would make more sense to malloc some stuff,
		instead of calling a bajillion writes.

		maybe add a char temp[MAX_DEFAULT_PADDING] and if n > MAX_DEFAULT_PADDING
		use malloc. A good size would maybe be 80, the default width of the terminal?

		should also be conscious of the cases malloc is called in when testing.
*/
/*
int	add_padding(int n, int c)
{
	char		*tmp;
	static char	stack_tmp[DEFAULT_MIN_FIELD_WIDTH];
	int			i;

	if (n == 0)
		return (0);
	if (n <= DEFAULT_MIN_FIELD_WIDTH)
	{
		ft_memset(stack_tmp, c, n);
		write(1, stack_tmp, n);
		return (n);
	}
	tmp = malloc(n);
	if (!tmp)
		return (-1);
	i = 0;
	ft_memset(tmp, c, n);
	write(1, tmp, n);
	free(tmp);
	return (n);
}
*/
/*
	while (--n > 0)
		write(1, &c | FLAG_DOT);
	return ;
*/
