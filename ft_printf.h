/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:39:27 by sancuta           #+#    #+#             */
/*   Updated: 2025/11/30 12:14:15 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft/libft.h"
# include <stdarg.h>

# define DEFAULT_MIN_FIELD_WIDTH 80
# define FLAG_MINUS	(1 << 0) // bits for '-': 00000001 =  1
# define FLAG_ZERO	(1 << 1) // bits for '0': 00000010 =  2
# define FLAG_HASH	(1 << 2) // bits for '#': 00000100 =  4
# define FLAG_SPACE	(1 << 3) // bits for ' ': 00001000 =  8
# define FLAG_PLUS	(1 << 4) // bits for '+': 00010000 = 16
# define FLAG_DOT	(1 << 5) // bits for '.': 00100000 = 32
# define FLAG_NEG	(1 << 6) // bits for n<0: 01000000 = 64
# define FLAG_SIGN	88		 // bits		: 01011000 = 64 + 16 + 8 = 88

typedef struct s_format_specifier
{
	unsigned int		field_width;
	unsigned int		precision;
	unsigned int		flag;
	unsigned int		conv_spec;
}	t_format_specifier;

typedef struct s_valid_spec
{
	unsigned int	spec;
	unsigned int	allowed_flags;
}	t_valid_spec;

/*const char	g_flags[] = "-0# +.";

const t_valid_spec	g_valid_spec[] =
{
	{'c', FLAG_MINUS},
	{'s', FLAG_MINUS | FLAG_DOT},
	{'d', FLAG_MINUS | FLAG_ZERO | FLAG_PLUS | FLAG_SPACE | FLAG_DOT},
	{'i', FLAG_MINUS | FLAG_ZERO | FLAG_PLUS | FLAG_SPACE | FLAG_DOT},
	{'u', FLAG_MINUS | FLAG_ZERO | FLAG_DOT},
	{'p', FLAG_MINUS},
	{'x', FLAG_MINUS | FLAG_ZERO | FLAG_HASH | FLAG_DOT},
	{'X', FLAG_MINUS | FLAG_ZERO | FLAG_HASH | FLAG_DOT},
};
*/

int					ft_printf(const char *s, ...);
t_format_specifier	get_format_specifier(const char **s, const char *mask_set);
int					get_mask_index(int c, const char *mask_set);
int					get_number(const char **s);
int					abs_nbr_len(int n);
int					print_arg(t_format_specifier data, va_list *args);
int					print_char(t_format_specifier data, int c);
int					print_str(t_format_specifier data, char *s);
int					add_padding(int n, int c);
int					print_int(t_format_specifier data, int n);
int					put_space(t_format_specifier data, int nb_len, int sign_len);
int					put_sign(t_format_specifier data);
int					put_zero(t_format_specifier data, int nb_len, int sign_len);
int					abs_nbr_len(int n);
int					put_nbr_base(int n, const char *base);
int					recurse(int n, const char *base, int base_len, int i);
int					ft_putchar(int c);

#endif
