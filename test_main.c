/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:18:29 by sancuta           #+#    #+#             */
/*   Updated: 2025/11/30 20:20:32 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>

#define FLAG_MINUS	(1 << 0) /* bits: 00000001*/
#define FLAG_ZERO	(1 << 1) /* bits: 00000010*/
#define FLAG_HASH	(1 << 2) /* bits: 00000100*/
#define FLAG_SPACE	(1 << 3) /* bits: 00001000*/
#define FLAG_PLUS	(1 << 4) /* bits: 00010000*/

typedef struct s_conv_spec
{
	uint32_t	spec;
	uint32_t	allowed_flags; /* bitmask */
	uint32_t	allow_precision;
}	t_conv_spec;

static const t_conv_spec	g_conv_specs[] = 
{
	{'c', FLAG_MINUS, 0},
	{'s', FLAG_MINUS, 1},
	{'d', FLAG_MINUS | FLAG_ZERO | FLAG_PLUS | FLAG_SPACE, 1},
	{'i', FLAG_MINUS | FLAG_ZERO | FLAG_PLUS | FLAG_SPACE, 1},
	{'u', FLAG_MINUS | FLAG_ZERO, 1},
	{'p', FLAG_MINUS, 0},
	{'x', FLAG_MINUS | FLAG_ZERO | FLAG_HASH, 1},
	{'X', FLAG_MINUS | FLAG_ZERO | FLAG_HASH, 1},
};

#define N_CMDS	(sizeof(g_conv_specs) / sizeof(*g_conv_specs))

static const char	g_flags[] = "-0# +";
static const int	widths[] = {0, 3, 5, 8, 10};
static const int	precisions[] = {0, 3, 5, 8, 10};

static void	build_flag(int mask, char *buf)
{
	size_t	i; // flag bit
	size_t	j; // index output buffer
	int		bit;

	i = 0;
	j = 0;
	while (g_flags[i])
	{
		bit = (1 << i);
		if (mask & bit)
		{
			buf[j] = g_flags[i];
			j++;
		}
		i++;
	}
	buf[j] = '\0';
}

int main(void)
{
	size_t	i;
	size_t	j;
	size_t	k;
	int		mask;
	char	flag_buf[8];

	i = 0;
	while (i < N_CMDS)
	{
		printf("ft_printf(\"=== %c ===\\n\");\n", g_conv_specs[i].spec);
		mask = 0;
		while (mask < 32)
		{
			if (mask & ~g_conv_specs[i].allowed_flags)
			{
				mask++;
				continue ;
			}
			build_flag(mask, flag_buf);
			j = 0;
			while (j < sizeof(widths) / sizeof(int))
			{
				if (g_conv_specs[i].allow_precision)
				{
					k = 0;
					while (k < sizeof(precisions) / sizeof(int))
					{
						if (g_conv_specs[i].spec == 's')
						{
							printf("ft_printf(\"Format: |%%%%%s%.0d.%.0d%c|		\");		", flag_buf, widths[j], precisions[k], g_conv_specs[i].spec);
							printf("ft_printf(\"|%%%s%.0d.%.0d%c|\\n\", \"hello world!\");\n", flag_buf, widths[j], precisions[k], g_conv_specs[i].spec);
							printf("ft_printf(\"Format: |%%%%%s%.0d%c|		\");		", flag_buf, widths[j], g_conv_specs[i].spec);
							printf("ft_printf(\"|%%%s%.0d%c|\\n\", \"hello world!\");\n", flag_buf, widths[j], g_conv_specs[i].spec);
							printf("ft_printf(\"Format: |%%%%%s.%.0d%c|		\");		", flag_buf, precisions[k], g_conv_specs[i].spec);
							printf("ft_printf(\"|%%%s.%.0d%c|\\n\", \"hello world!\");\n", flag_buf, precisions[k], g_conv_specs[i].spec);
							printf("ft_printf(\"Format: |%%%%%s%c|		\");		", flag_buf, g_conv_specs[i].spec);
							printf("ft_printf(\"|%%%s%c|\\n\", \"hello world!\");\n", flag_buf, g_conv_specs[i].spec);
						}
						else if (g_conv_specs[i].spec != 'c')
						{
							printf("ft_printf(\"Format: |%%%%%s%.0d.%.0d%c|		\");		", flag_buf, widths[j], precisions[k], g_conv_specs[i].spec);
							printf("ft_printf(\"|%%%s%.0d.%.0d%c|\\n\", 42);\n", flag_buf, widths[j], precisions[k], g_conv_specs[i].spec);
							printf("ft_printf(\"Format: |%%%%%s%.0d.%.0d%c|		\");		", flag_buf, widths[j], precisions[k], g_conv_specs[i].spec);
							printf("ft_printf(\"|%%%s%.0d.%.0d%c|\\n\", -42);\n", flag_buf, widths[j], precisions[k], g_conv_specs[i].spec);
							printf("ft_printf(\"Format: |%%%%%s%.0d.%.0d%c|		\");		", flag_buf, widths[j], precisions[k], g_conv_specs[i].spec);
							printf("ft_printf(\"|%%%s%.0d.%.0d%c|\\n\", 0);\n", flag_buf, widths[j], precisions[k], g_conv_specs[i].spec);
							printf("ft_printf(\"Format: |%%%%%s%.0d%c|		\");		", flag_buf, widths[j], g_conv_specs[i].spec);
							printf("ft_printf(\"|%%%s%.0d%c|\\n\", 42);\n", flag_buf, widths[j], g_conv_specs[i].spec);
							printf("ft_printf(\"Format: |%%%%%s%.0d%c|		\");		", flag_buf, widths[j], g_conv_specs[i].spec);
							printf("ft_printf(\"|%%%s%.0d%c|\\n\", -42);\n", flag_buf, widths[j], g_conv_specs[i].spec);
							printf("ft_printf(\"Format: |%%%%%s%.0d%c|		\");		", flag_buf, widths[j], g_conv_specs[i].spec);
							printf("ft_printf(\"|%%%s%.0d%c|\\n\", 0);\n", flag_buf, widths[j], g_conv_specs[i].spec);
							printf("ft_printf(\"Format: |%%%%%s.%.0d%c|		\");		", flag_buf, widths[j], g_conv_specs[i].spec);
							printf("ft_printf(\"|%%%s.%.0d%c|\\n\", 42);\n", flag_buf, precisions[k], g_conv_specs[i].spec);
							printf("ft_printf(\"Format: |%%%%%s.%.0d%c|		\");		", flag_buf, precisions[k], g_conv_specs[i].spec);
							printf("ft_printf(\"|%%%s.%.0d%c|\\n\", -42);\n", flag_buf, precisions[k], g_conv_specs[i].spec);
							printf("ft_printf(\"Format: |%%%%%s.%.0d%c|		\");		", flag_buf, precisions[k], g_conv_specs[i].spec);
							printf("ft_printf(\"|%%%s.%.0d%c|\\n\", 0);\n", flag_buf, precisions[k], g_conv_specs[i].spec);
							printf("ft_printf(\"Format: |%%%%%s%c|		\");		", flag_buf, g_conv_specs[i].spec);
							printf("ft_printf(\"|%%%s%c|\\n\", 42);\n", flag_buf, g_conv_specs[i].spec);
							printf("ft_printf(\"Format: |%%%%%s%c|		\");		", flag_buf, g_conv_specs[i].spec);
							printf("ft_printf(\"|%%%s%c|\\n\", -42);\n", flag_buf, g_conv_specs[i].spec);
							printf("printf(\"Format: |%%%%%s%c|		\");		", flag_buf, g_conv_specs[i].spec);
							printf("printf(\"|%%%s%c|\\n\", 0);\n", flag_buf, g_conv_specs[i].spec);
						}
						k++;
					}
				}
				if (g_conv_specs[i].spec == 'c')
				{
					printf("ft_printf(\"Format: |%%%%%s%.0d%c|		\");		", flag_buf, widths[j], g_conv_specs[i].spec);
					printf("ft_printf(\"|%%%s%.0d%c|\\n\", 'a');\n", flag_buf, widths[j], g_conv_specs[i].spec);
				}
				else if (g_conv_specs[i].spec == 'p')
				{
					printf("ft_printf(\"Format: |%%%%%s%.0d%c|		\");		", flag_buf, widths[j], g_conv_specs[i].spec);
					printf("ft_printf(\"|%%%s%.0d%c|\\n\", (int *)4200);\n", flag_buf, widths[j], g_conv_specs[i].spec);
				}
				j++;
			}
			mask++;
		}
		i++;
	}
	return (0);
}
