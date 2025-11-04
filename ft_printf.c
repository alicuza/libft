/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:55:17 by sancuta           #+#    #+#             */
/*   Updated: 2025/11/04 20:35:45 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdarg.h>
#include <stdio.h>

/*
	flags		'-' '0' '#' '+' ' '
				 0   0   0   0   0
				 0   1   2   3   4
	type char	'c' 's' 'p''d/i''u' 'x' 'X'
				 0   0   0   0   0   0   0
				 5   6   7   8   9  10  11

	'+'	doesn't work with 'c', 's', 'p', 'u', 'x', 'X'
	'#' doesn't work with 'c', 's', 'p', 'd/i', 'u'
	'0' doesn't work with 'c', 's', 'p',
	' ' doesn't work with 'c', 'p', 's', 'u', 'x', 'X'

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

int	ft_printf(const char *s, ...);
t_format_specifier	get_format_specifier(const char **s);
int	get_mask_index(char c, const char *mask_set);
char	construct_mask(const char **s, const char *mask_set, const char *mask);
int	get_number(const char **s);

const char	g_flag_mask[6] = {0x10, 0x8, 0x4, 0x2, 0x1, '\0'};
const char	g_flags[6] = "-0#+ ";
const char	g_type_char_mask[8] = {0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1, '\0'};
const char	g_type_chars[8] = "cspduxX";

int main(void)
{
	ft_printf("hello %0-+20.10d\n");
}

int	ft_printf(const char *s, ...)
{
	size_t				res;
//	size_t				tmp;
	va_list				args;
	t_format_specifier	to_print;

	va_start(args, s);
	res = 0;
	if (!s)
		return (-1);
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			if (*s == '%')
			{
				putchar(*s);
				s++;
				continue;
			}
			to_print = get_format_specifier(&s);
			printf("flag_mask = %x, type_char_mask = %x, field_width = %d, precision = %d\n", to_print.flag, to_print.type_char, to_print.field_width, to_print.precision);
//			tmp = print_stuff(to_print); // supposed to contain count the number of characters printed
//			res += tmp;
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
	res.flag = construct_mask(s, g_flags, g_flag_mask);
	res.field_width = get_number(s);
	if (**s == '.')
	{
		(*s)++;
		res.precision = get_number(s);
	}
	res.type_char = construct_mask(s, g_type_chars, g_type_char_mask);
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

char	construct_mask(const char **s, const char *mask_set, const char *mask)
{
	char	ret;
	int		ind;

	ret = 0;
	ind = get_mask_index(**s, mask_set);
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
