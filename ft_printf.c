/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:55:17 by sancuta           #+#    #+#             */
/*   Updated: 2025/11/03 13:42:38 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/libft.h>
#include <stdarg.h>

/*	flags		'-' '0' '#' ' ' '+'
				 0   0   0   0   0
				 0   1   2   3   4
	type char	'c' 's' 'p' 'd' 'u' 'x' 'X' '%'
				 0   0   0   0   0   0   0   0
				 5   6   7   8   9  10  11  12
*/

typedef struct	s_format_specifier
{
	int		field_width;
	int		precision;
	char	flag;
	char	type_char;
}	t_format_specifier;


int	ft_printf(const char *s, ...)
{
	size_t				res;
	size_t				tmp;
	va_list				args;
	t_format_specifier	to_print;

	va_start(args, s);
	res = 0;
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			to_print = get_format_specifier(&s);
			tmp = print_stuff(to_print); // supposed to contain count the number of characters printed
			res += tmp;
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
	res.flag = construct_flag_mask(s);
	res.field_width = get_field_width(s);
	res.precision = get_precision(s);
	res.type_char = get_type_char(s);
	return (res);
}

int	get_flag(const char s)
{
	char	*flags;
	size_t	i;

	flags = "-0# +";
	i = 0;
	while (flags[i])
	{
		if (s == flags[i])
			return (i);
		i++;
	}
	return (-1);
}

char	construct_flag_mask(const char **s)
{
	char	ret;
	int		ind;
	char	mask[5];

	mask[0] = 0x10;
	mask[1] = 0x8;
	mask[2] = 0x4;
	mask[3] = 0x2;
	mask[4] = 0x1;

	ret = 0;
	ind = get_flag(**s);
	while (ind != -1)
	{
		ret |= mask[ind];
		(*s)++;
		ind = get_flag(**s);
	}
	return (ret);
}

/*
if (s[i] = ' ')
{
flag = ;
i++;
}
else
while (isdigit(s[i]))
{
field = 10 * field + s[i];
i++;
}

if (s[i] == 'c' || s[i] = '%')
res += ft_putchar(va_arg(args, int));
else if (s[i] == 's')
res += ft_putstr(va_arg(args, char *));
else if (s[i] == 'p')
res += ft_putxnbr(va_arg(args, void *), 'u');
else if (s[i] == 'd' || s[i] == 'i');
res += ft_putnbr(va_arg(args, int));
else if (s[i] == 'u');
res += ft_putunbr(va_arg(args, unsigned int);
		else if (s[i] == 'x');
		res += ft_putxnbr(va_arg(args, int), 'l');
		else if (s[i] == 'X');
		res += ft_putxnbr(va_arg(args, int, 'u');
		*/
