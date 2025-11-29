/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:38:01 by sancuta           #+#    #+#             */
/*   Updated: 2025/11/29 20:59:04 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_int(t_format_specifier data, int n)
{
	int ret;
	int	nb_len;
	int	sign_len;
	
	ret = 0;
	sign_len = 0;
	nb_len = abs_nbr_len(n);
	if ((n < 0) || (data.flag & FLAG_SIGN))
	{
		data.flag |= FLAG_NEG;
		sign_len++;
	}
	if (!(data.flag & (FLAG_MINUS | FLAG_ZERO | FLAG_DOT)))
		ret += put_space(data, nb_len, sign_len);
	if (data.flag & FLAG_SIGN)
		ret += put_sign(data);
	if (data.flag & FLAG_ZERO | FLAG_DOT)
		ret += put_zero(data, nb_len, sign_len);
	ret += put_nbr_base(n, "0123456789");
	if (data.flag & FLAG_MINUS && !(data.flag & (FLAG_ZERO | FLAG_DOT)))
		ret += put_space(data, nb_len, sign_len);
	return(ret);
}

int	put_space(t_format_specifier data, int nb_len, int sign_len)
{
	int	i;
	int	len;

	len = sign_len;
	if (nb_len < data.precision)
		nb_len = data.precision;
	len += nb_len;
	i = data.field_width - len;
	while (i > 0)
	{
		write(1, " ", 1);
		i--;
	}
	return (data.field_width - len);
}

int	put_sign(t_format_specifier data)
{
	if (data.flag & FLAG_SPACE)
		return (write(1, " ", 1));
	else if (data.flag & FLAG_PLUS)
		return (write(1, "+", 1));
	else if (data.flag & FLAG_NEG)
		return (write(1, "-", 1));
	else if ((data.flag & FLAG_HASH)
			&& ((data.conv_spec == 'x') || (data.conv_spec == 'p')))
		return (write(1, "0x", 2));
	else if ((data.flag & FLAG_HASH) && (data.conv_spec == 'X'))
		return (write(1, "0X", 2));
	else
		return (0);
}

int	put_zero(t_format_specifier data, int nb_len, int sign_len)
{
	if ((data.flag & FLAG_ZERO) && data.field_width > nb_len + sign_len)
		return (write(1, "0", data.field_width - nb_len - sign_len));
	else if ((data.flag & FLAG_DOT) && data.precision > nb_len)
		return (write(1, "0", data.precision - nb_len));
	else
		return (0);
}

int	put_nbr_base(int n, const char *base)
{
	int	base_len;

	base_len = ft_strlen(base);
	return (recurse(n, base, base_len, 0));
}

int	recurse(int n, const char *base, int base_len, int i)
{
	int sign;
	int condition;

	condition = (n >= base_len);
	sign = 1;
	if (n < 0)
	{
		sign = -sign;
		condition = (n <= -base_len);
	}
	if (condition)
		return (recurse(n / base_len, base, base_len, i + 1));
	ft_putchar(base[(n % base_len) * sign]);
	return (i + 1);
}

int ft_putchar(int c)
{
	return (write(1, &c, 1));
}
