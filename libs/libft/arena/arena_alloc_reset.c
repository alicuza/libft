/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_alloc_reset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:27:38 by sancuta           #+#    #+#             */
/*   Updated: 2026/05/27 21:18:09 by sancuta          ###   ########.fr       */
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
	arena->offset = (arena->offset + (align - 1)) & ~(align - 1);
}
/* static void	arena_grow_error_handler(t_arena *arena)
{
	perror("arena_grow");
	if (arena->clean && arena->env)
		arena->clean(arena->env);
	arena_free(arena);
	exit(EXIT_FAILURE);
} */

static bool	arena_grow(t_arena *arena, size_t size)
{
	void	*new_buffer;

    while (arena->cap + arena->sentinel - arena->offset < size)
    {
        if (arena->cap > HALF_SIZE_MAX)
		    return (false);
    	arena->cap *= 2;
    }
	new_buffer = malloc(arena->cap + arena->sentinel);
	if (!new_buffer)
		return (false);
	ft_memmove(new_buffer, arena->buf, arena->offset);
	ft_memset(new_buffer + arena->offset, 0,
		arena->cap + arena->sentinel - arena->offset);
	free(arena->buf);
	arena->buf = new_buffer;
	return (true);
}

size_t	arena_alloc(t_arena *arena, size_t size, size_t align)
{
	size_t	offset;

	arena_align(arena, align);
	if (size > (arena->cap + arena->sentinel - arena->offset)
		&& !arena_grow(arena, size))
		arena->offset = 0;
	offset = arena->offset;
	arena->offset += size;
	return (offset);
}

void	arena_reset(t_arena *arena)
{
	arena->offset = arena->sentinel;
}

void	arena_clear(t_arena *arena)
{
	ft_memset(arena->buf + arena->sentinel, 0, arena->offset - arena->sentinel);
	arena->offset = arena->sentinel;
}
