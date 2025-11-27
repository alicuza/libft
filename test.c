/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:18:29 by sancuta           #+#    #+#             */
/*   Updated: 2025/10/27 12:35:38 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>

#define FLAG_MINUS	(1 << 0) /* bits: 00000001*/
#define FLAG_ZERO	(1 << 1) /* bits: 00000010*/
#define FLAG_HASH	(1 << 2) /* bits: 00000100*/
#define FLAG_SPACE	(1 << 3) /* bits: 00001000*/
#define FLAG_PLUS	(1 << 4) /* bits: 00010000*/

typedef struct s_spec
{
	uint32_t	conv;
	uint32_t	allowed_flags; /* bitmask */
	uint32_t	allow_precision;
}	t_spec;


static const char g_flag_opts[] = "-0# +";

int main(void)
{
	
}
