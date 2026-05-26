/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_transform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 16:51:36 by sancuta           #+#    #+#             */
/*   Updated: 2026/05/26 16:52:03 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_idx_from_offset(t_arena *arena, size_t offset)
{
	return (offset / arena->sentinel);
}

size_t	get_offset_from_idx(t_arena *arena, size_t idx)
{
	return (idx * arena->sentinel);
}

t_token	*get_token_from_offset(t_arena *arena, size_t offset)
{
	return ((t_token *)(arena->buf + offset));
}

t_token	*get_token_from_idx(t_arena *arena, size_t idx)
{
	return ((t_token *)(arena->buf + idx * arena->sentinel));
}
