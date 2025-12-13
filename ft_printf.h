/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:39:27 by sancuta           #+#    #+#             */
/*   Updated: 2025/12/12 14:55:07 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft/libft.h"
# include <stdarg.h>

# define DEFAULT_MIN_FIELD_WIDTH 80
# define FLAG_MINUS	1 //(1 << 0) // bits for '-': 00000001 =  1
# define FLAG_ZERO	2 //(1 << 1) // bits for '0': 00000010 =  2
# define FLAG_HASH	4 //(1 << 2) // bits for '#': 00000100 =  4
# define FLAG_PLUS	8 //(1 << 3) // bits for '+': 00001000 =  8
# define FLAG_SPACE	16 //(1 << 4) // bits for ' ': 00010000 = 16
# define FLAG_DOT	32 //(1 << 5) // bits for '.': 00100000 = 32
# define FLAG_NEG	64 //(1 << 6) // bits for n<0: 01000000 = 64
# define FLAG_SIGN	88 //(FLAG_NEG | FLAG_PLUS | FLAG_SPACE) // bits: 01011000 = 64 + 16 + 8 = 88

typedef struct s_format_specifier
{
	int					field_width;
	int					precision;
	unsigned int		flag;
	int					conv_spec;
}	t_format_specifier;

extern const char	g_valid_conv_spec[];
extern const char	g_valid_flags[];
extern const int	g_allowed_flags[];

int					ft_printf(const char *s, ...);
t_format_specifier	get_format_specifier(const char **s, const char *mask_set);
int					get_number(const char **s);
int					print_arg(t_format_specifier *data, va_list *args);
int					print_char(t_format_specifier *data, int c);
int					print_str(t_format_specifier *data, char *s);
int					print_int(t_format_specifier *data, int n);
int					print_ptr(t_format_specifier *data, unsigned long n);
int					print_hex(t_format_specifier *data, unsigned long n, const char *base);
int					print_uint(t_format_specifier *data, unsigned int n);
int					put_space(t_format_specifier *data, int nb_len, int sign_len);
int					put_sign(t_format_specifier *data);
int					put_zero(t_format_specifier *data, int nb_len, int sign_len);
int					abs_nbr_len(unsigned long n, unsigned long base);
int					put_nbr_base(unsigned long n, const char *base);
int					recurse(unsigned long n, const char *base, unsigned long base_len, int i);
int					ft_putchar(int c);
ssize_t				ft_indchr(const char *s, int c);
#endif
