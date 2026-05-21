/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_init_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 08:36:13 by sancuta           #+#    #+#             */
/*   Updated: 2026/05/12 16:51:00 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"
#include "../libft.h"

t_arena	arena_init(size_t size, size_t sentinel)
{
	t_arena	arena;

	ft_memset(&arena, 0, sizeof(t_arena));
	arena.sentinel = sentinel;
	if (!size)
		return (arena);
	arena.buf = malloc(size + sentinel);
	if (!arena.buf)
		return (arena);
	ft_memset(arena.buf, 0, size + sentinel);
	arena.cap = size;
	arena.offset = arena.sentinel;
	return (arena);
}

void	arena_free_buf(t_arena *arena)
{
	free(arena->buf);
	ft_memset(arena, 0, sizeof(t_arena));
}

void	arena_hook_cleanup(t_arena *arena, void (*clean)(void *), void *env)
{
	arena->clean = clean;
	arena->env = env;
}
