/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 21:48:29 by sancuta           #+#    #+#             */
/*   Updated: 2026/05/22 21:48:40 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void  print_arena(t_arena *arena)
{
  printf("string_arena\n\tbuffer address = %p\n\toffset = %lu\n\tcapacity = %lu\n\tsentinel = %lu\n", arena->buf, arena->offset, arena->cap, arena->sentinel);
  printf("head:\n");
  ft_print_memory(arena, sizeof(t_arena));
  printf("buffer:\n");
  ft_print_memory(arena->buf, arena->cap + arena->sentinel);
  arena_reset(arena);
}

