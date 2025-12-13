/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:38:01 by sancuta           #+#    #+#             */
/*   Updated: 2025/12/12 02:19:46 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_int(t_format_specifier *data, int n)
{
	int	ret;
	int	nb_len;
	int	sign_len;
	
	ret = 0;
	sign_len = 0;
	nb_len = abs_nbr_len((unsigned long)n, 10);
	if (data->precision == -1)
		data->precision = 1;
	if (n < 0)
	{
		data->flag |= FLAG_NEG;
		nb_len = abs_nbr_len((unsigned long)(-(long)n), 10);
	}
	else if (!n && !data->precision)
		nb_len = 0;
	if (data->flag & FLAG_SIGN)
		sign_len++;
	if (!(data->flag & (FLAG_MINUS | FLAG_ZERO)))
		ret += put_space(data, nb_len, sign_len);
	if (data->flag & FLAG_SIGN)
		ret += put_sign(data);
	if (data->flag & (FLAG_ZERO | FLAG_DOT))
		ret += put_zero(data, nb_len, sign_len);
	if (nb_len)
	{
		if (data->flag & FLAG_NEG)
			ret += put_nbr_base((unsigned long)(-(long)n), "0123456789");
		else
			ret += put_nbr_base((unsigned long)n, "0123456789");
	}
	if (data->flag & FLAG_MINUS)
		ret += put_space(data, nb_len, sign_len);
	return(ret);
}

int	print_uint(t_format_specifier *data, unsigned int n)
{
	int	ret;
	int	nb_len;
	
	ret = 0;
	nb_len = abs_nbr_len((unsigned long)n, 10);
	if (data->precision == -1)
		data->precision = 1;
	if (!n && !data->precision)
		nb_len = 0;
	if (!(data->flag & (FLAG_MINUS | FLAG_ZERO)))
		ret += put_space(data, nb_len, 0);
	if (data->flag & (FLAG_ZERO | FLAG_DOT))
		ret += put_zero(data, nb_len, 0);
	if (nb_len)
		ret += put_nbr_base(n, "0123456789");
	if (data->flag & FLAG_MINUS)
		ret += put_space(data, nb_len, 0);
	return(ret);
}

int	print_ptr(t_format_specifier *data, unsigned long n)
{
	if (!n)
		return (write(1, "(nil)", 5));
	data->flag |= FLAG_HASH;
	return (print_hex(data, n, "0123456789abcdef"));
}

int	print_hex(t_format_specifier *data, unsigned long n, const char *base)
{
	int	ret;
	int	nb_len;
	int	sign_len;
	
	ret = 0;
	sign_len = 0;
	nb_len = abs_nbr_len(n, 16);
	if (data->precision == -1)
		data->precision = 1;
	if (!n && !data->precision)
		nb_len = 0;
	if ((data->flag & FLAG_HASH) && n)
		sign_len += 2;
	if (!(data->flag & (FLAG_MINUS | FLAG_ZERO)))
		ret += put_space(data, nb_len, sign_len);
	if ((data->flag & FLAG_HASH) && n)
		ret += put_sign(data);
	if (data->flag & (FLAG_ZERO | FLAG_DOT))
		ret += put_zero(data, nb_len, sign_len);
	if (nb_len)
		ret += put_nbr_base(n, base);
	if (data->flag & FLAG_MINUS)
		ret += put_space(data, nb_len, sign_len);
	return(ret);
}

int	put_space(t_format_specifier *data, int arg_len, int sign_len)
{
	int	i;
	int	len;

	len = sign_len;
	if (data->conv_spec == 's')
	{
		if ((data->precision != -1) && (arg_len > data->precision))
			arg_len = data->precision;
	}
	else
	{
		if ((data->precision != -1) && (arg_len < data->precision))
			arg_len = data->precision;
	}
	len += arg_len;
	i = data->field_width - len;
	if (i <= 0)
		return (0);
	while (i > 0)
	{
		write(1, " ", 1);
		i--;
	}
	return (data->field_width - len);
}

int	put_sign(t_format_specifier *data)
{
	if ((data->flag & FLAG_HASH))
	{
		if (data->conv_spec == 'X')
			return (write(1, "0X", 2));
		else
			return (write(1, "0x", 2));
	}
	else if (data->flag & FLAG_NEG)
		return (write(1, "-", 1));
	else if (data->flag & FLAG_PLUS)
		return (write(1, "+", 1));
	else if (data->flag & FLAG_SPACE)
		return (write(1, " ", 1));
	else
		return (0);
}

int	put_zero(t_format_specifier *data, int nb_len, int sign_len)
{
	int	len;
	int	i;

	len = 0;
	if ((data->flag & FLAG_ZERO) && data->field_width > nb_len + sign_len)
		len = data->field_width - nb_len - sign_len;
	else if ((data->flag & FLAG_DOT) && data->precision > nb_len)
		len = data->precision - nb_len;
	i = 0;
	while (i < len)
	{
		write(1, "0", 1);
		i++;
	}
	return (len);
}

int	put_nbr_base(unsigned long n, const char *base)
{
	unsigned long	base_len;

	base_len = ft_strlen(base);
	return (recurse(n, base, base_len, 0));
}

int	recurse(unsigned long n, const char *base, unsigned long base_len, int i)
{
	if (n >= base_len)
		i = recurse(n / base_len, base, base_len, i);
	ft_putchar(base[n % base_len]);
	return (i + 1);
}

int ft_putchar(int c)
{
	return (write(1, &c, 1));
}

ssize_t	ft_indchr(const char *s, int c)
{
	ssize_t	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return (i);
		i++;
	}
	if ((unsigned char)s[i] == (unsigned char)c)
		return (i);
	return (-1);
}
