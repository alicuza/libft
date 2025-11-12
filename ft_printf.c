/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:55:17 by sancuta           #+#    #+#             */
/*   Updated: 2025/11/12 16:30:25 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdarg.h>
#include <stdio.h>

#define DEFAULT_MIN_FIELD_WIDTH 80

/*
	flags		'-' '0' '#' '+' ' ' '.' given int n < 0 -> should print '-'
				 0   0   0   0   0   0   0
				 0   1   2   3   4   5   6
	type char	'c' 's' 'p''d/i''u' 'x' 'X'
				 0   0   0   0   0   0   0
				 5   6   7   8   9  10  11
				 0   1   2   3   4   5   6
	p_ind		' ' '0'
				 0   1

	'0' doesn't work with 'c', 's', 'p',
	'#' doesn't work with 'c', 's', 'p', 'd/i', 'u'
	'+' doesn't work with 'c', 's', 'p', 'u', 'x', 'X'
	' ' doesn't work with 'c', 's', 'p', 'u', 'x', 'X'

	'+' overrides ' '
	'-' overrides '0'
	'.' overrides '0'

	precision doesn't work with 'c', 'p'
	field width works with everything

	only -0. interact with each other.
	the other flags don't interact with
	them, and can be handled separately?
*/

typedef struct	s_format_specifier
{
	int		field_width;
	int		precision;
	char	flag;
	char	type_char;
}	t_format_specifier;

typedef union	u_arg
{
	char			c;
	void			*s;
	int				d;
	unsigned int	u;
}	t_arg;

int	ft_printf(const char *s, ...);
t_format_specifier	get_format_specifier(const char **s);
int	get_mask_index(char c, const char *mask_set);
char	construct_mask(const char **s, const char *mask_set, const char *mask);
int	get_number(const char **s);

const char	g_flag_mask[7] = {0x40, 0x20, 0x10, 0x8, 0x4, 0x2, '\0'};
const char	g_flags[7] = "-0#+ .";
const char	g_type_char_mask[8] = {0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1, '\0'};
const char	g_type_chars[8] = "cspduxX";

int main(void)
{
	ft_printf("hello %0-+20.10d\n");
}

int	ft_printf(const char *s, ...)
{
	size_t				res;
	size_t				cnt;
	va_list				args;
	t_format_specifier	format_data;

	va_start(args, s);
	res = 0;
	if (!s)
		return (-1);
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			if (!(*s))
				return (-1);
			if (*s == '%')
			{
				putchar(*s);
				s++;
				continue;
			}
			to_print = get_format_specifier(&s);
//			printf("flag_mask = %x, type_char_mask = %x, field_width = %d, precision = %d\n", to_print.flag, to_print.type_char, to_print.field_width, to_print.precision);
			cnt = print_arg(format_data, &args);
			if (cnt == -1)
				return (-1);
			res += cnt;
		}
		else
		{
			res += putchar(*s);
			s++;
		}
	}
	return (res);
}

t_format_specifier	get_format_specifier(const char **s)
{
	t_format_specifier	res;

	res = (t_format_specifier){0};
	res.flag = construct_mask(s, g_flags, g_flag_mask, 0);
	res.field_width = get_number(s);
	if (**s == ".")
	{
		res.flag |= g_flag_mask[5]
		res.precision = get_number(s);
	}
	res.type_char = construct_mask(s, g_type_chars, g_type_char_mask, 1);
	return (res);
}

int	get_mask_index(char c, const char *mask_set)
{
	size_t	i;

	i = 0;
	while (mask_set[i])
	{
		if (c == mask_set[i])
			return (i);
		i++;
	}
	return (-1);
}

char	construct_mask(const char **s, const char *mask_set, const char *mask, int only_one)
{
	char	ret;
	int		ind;

	ret = 0;
	ind = get_mask_index(**s, mask_set);
	if (only_one)
		return (mask[ind]);
	while (ind != -1)
	{
		ret |= mask[ind];
		(*s)++;
		ind = get_mask_index(**s, mask_set);
	}
	return (ret);
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

int	print_arg(t_format_specifier data, va_list *args)
{
	int		ret;
	t_arg	arg;

	ret = 0
	if (data.type_char & g_type_char_mask[0] == g_type_char_mask[0])
		ret = print_char(va_arg(*args, int));
	else if (data.type_char & g_type_char_mask[1] == g_type_char_mask[1])
		ret = print_str(va_arg(*args, char *));
	else if (data.type_char & g_type_chr_mask[2] == g_type_char_mask[2])
		ret = print_ptr(va_arg(*args, void *));
	else if (data.type_char & g_type_chr_mask[3] == g_type_char_mask[3])
		ret = print_int(va_arg(*args, int));
	else if (data.type_char & g_type_chr_mask[4] == g_type_char_mask[4])
		ret = print_uint(va_arg(*args, unsigned int));
	else if (data.type_char & g_type_chr_mask[5] == g_type_char_mask[5])
		ret = print_ptr(va_arg(*args, unsigned int));
	else if (data.type_char & g_type_chr_mask[6] == g_type_char_mask[6])
		ret = print_ptr(va_arg(*args, unsigned int));
	return (ret);
}

int	print_char(t_format_specifier data, int c)
{
	if (data.field_width > 1)
	{
		if (data.flag & g_flag_mask[0] == g_flag_mask[0])
		{
			write(1, &c, 1);
			if(!add_padding(data.field_width - str_len, ' '))
				return (-1);
		}
		if(!add_padding(data.field_width - 1, ' '))
			return (-1);
		write(1, args, 1);
		return (data.field_width);
	}
	else
		write(1, args, 1);
	return (1);
}

int	print_str(t_format_specifier data, char *s)
{
	size_t	arg_len;

	arg_len = ft_strlen(s);
	if (arg_len > data.precision)
		arg_len = data.precision;
	if (data.field_width > arg_len)
	{
		if (data.flag & g_flag_mask[0] == g_flag_mask[r])
		{
			write(1, args, arg_len);
			if(!add_padding(data.field_width - arg_len, ' '))
				return (-1);
		}
		if(!add_padding(data.field_width - arg_len, ' '))
			return (-1);
		write(1, args, arg_len);
		return (data.field_width);
	}
	else
		write(1, args, arg_len);
	return (arg_len);
}
int	print_ptr(t_format_specifier data, void *ptr)
{
	char	*ret;
	size_t	arg_len;

	ret = convert_base(ptr, "0123456789abcdef");
	if (!ret)
		return (-1);
	arg_len = ft_strlen(ret);
	if (data.field_width > arg_len)
	{
		if (data.flag & g_flag_mask[0] == g_flag_mask[0])
		{
			write(1, args, arg_len);
			if(!add_padding(data.field_width - arg_len, ' '))
				return (-1);
		}
		if(!add_padding(data.field_width - arg_len, ' '))
			return (-1);
		write(1, args, arg_len);
		return (data.field_width);
	}
	else
		write(1, args, arg_len);
	return (arg_len);
}

int	print_int(t_format_specifier data, int n)
{
	char	pad;
	int		nbr_len;
	int		arg_len;

	if (n < 0)
		data.flags |= 0x1;
	nbr_len = abs_nbr_len(n);
	arg_len = nbr_len;
	if (arg_len < data.precision)
		arg_len = data.precision;
	if (data.field_width > arg_len)
	{
		if (data.flag & g_flag_mask[1] == g_flag_mask[1])
			pad = '0';
		if (data.flag & g_flag_mask[5] == g_flag_mask[5])
			pad = ' ';
		if (data.flag & g_flag_mask[0] == g_flag_mask[0])
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

int	abs_nbr_len(int n);
{
	int i;
	
	i = 0;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*convert_base(va_list args, )
{
	
}

	/*
		think about whether it would make more sense to malloc some stuff,
		instead of calling a bajillion writes.

		maybe add a char temp[MAX_DEFAULT_PADDING] and if n > MAX_DEFAULT_PADDING
		use malloc. A good size would maybe be 80, the default width of the terminal?

		should also be conscious of the cases malloc is called in when testing.
	*/
int	add_padding(size_t n, int c)
{
	char	*tmp;
	char	stack_tmp[DEFAULT_MIN_FIELD_WIDTH];
	size_t	i;

	if (n = 0)
		return (0);
	if (n <= DEFAULT_MIN_FIELD_WIDTH)
	{
		stack_tmp = memset(stack_tmp, c, DEFAULT_FIELD_WIDTH);
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

/*
	while (--n > 0)
		write(1, &c, 1);
	return ;
*/
}
