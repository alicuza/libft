/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 20:05:14 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/21 20:26:00 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

size_t	arena_memcpy(t_arena *dest, const void *src, size_t size)
{
	size_t	offset;

	offset = arena_alloc(dest, size, dest->align);
	ft_memcpy(dest->buf + offset, src, size);
	return (offset);
}

size_t	arena_memset(t_arena *data, int c, size_t size)
{
	size_t	offset;

	offset = arena_alloc(data, size, data->align);
	ft_memset(data->buf + offset, c, size);
	return (offset);
}

size_t	arena_strlcpy(t_arena *dest, const void *src, size_t size)
{
	size_t	offset;

	offset = arena_alloc(dest, size, 1);
	ft_strlcpy(dest->buf + offset, src, size);
	return (offset);
}
