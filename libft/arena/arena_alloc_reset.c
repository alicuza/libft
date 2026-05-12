/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_alloc_reset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:27:38 by sancuta           #+#    #+#             */
/*   Updated: 2026/05/12 17:11:59 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "arena.h"
#include <errno.h>
#include <string.h>

/*
 * natural alignment of 64bit systems is 8
 */

static inline void	arena_align(t_arena *arena, size_t align)
{
	arena->used = (arena->used + (align - 1)) & ~(align - 1);
}

static void	arena_grow(t_arena *arena)
{
	void	*new_buffer;

	if (arena->cap > HALF_SIZE_MAX)
	{
		if (arena->clean && arena->env)
			arena->clean(arena->env);
		return ;
	}
	new_buffer = malloc(arena->cap * 2);
	if (!new_buffer)
	{
		if (arena->clean && arena->env)
			arena->clean(arena->env);
		return ;
	}
	ft_memmove(new_buffer, arena->buf, arena->used);
	ft_memset(new_buffer + arena->used, 0, arena->cap - arena->used);
	arena->buf = new_buffer;
}

size_t	arena_alloc(t_arena *arena, size_t size, size_t align)
{
	size_t	offset;

	arena_align(arena, align);
	if (size > (arena->cap - arena->used))
		arena_grow(arena);
	offset = arena->used;
	arena->used += size;
	return (offset);
}

void	arena_reset(t_arena *arena, size_t align)
{
	arena->used = 0;
}
