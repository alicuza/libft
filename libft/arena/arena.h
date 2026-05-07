/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:41:35 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/26 16:26:09 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_H
# define ARENA_H

# include <stdlib.h>
# include "../libft.h"
# define HALF_SIZE_MAX (SIZE_MAX >> 2)

typedef enum e_align
{
    ALIGN_NONE,
    ALIGN_CHAR,
    ALIGN_INT,
    ALIGN_LONG,
    ALIGN_COUNT
}   t_align;

typedef struct s_arena
{
    t_align align;
	char	*buf;
	size_t	used;
	size_t	cap;
	void	(*clean)(void *);
	void	*env;
}	t_arena;

t_arena	arena_init(size_t cap);
size_t	arena_alloc(t_arena *arena, size_t size);
void	arena_reset(t_arena *arena);
size_t	arena_memset(t_arena *data, int c, size_t size);
size_t	arena_memcpy(t_arena *dest, const void *src, size_t size);
size_t	arena_strlcpy(t_arena *dest, const void *src, size_t size);
size_t	arena_split(t_arena *dest, const char *src, char del);
size_t	arena_save(t_arena *arena);
void	arena_restore(t_arena *arena, size_t idx);
void	arena_hook_cleanup(t_arena *arena, void (*clean)(void *), void *env);
void	arena_free(t_arena *arena);
void	*get_arena_ptr(t_arena *arena, size_t idx);
#endif
