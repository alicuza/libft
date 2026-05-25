/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 13:03:51 by sancuta           #+#    #+#             */
/*   Updated: 2026/05/25 18:33:28 by sancuta          ###   ########.fr       */
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

size_t	start_token(t_arena *arena, size_t start, t_token_type type)
{
	t_token	*token;
	size_t offset;

	offset = arena_alloc(arena, sizeof(t_token), _Alignof(t_token));
	printf("in arena_start_token at offset %zu\n", offset);
	token = get_token_from_offset(arena, offset);
	token->content.start = start;
	token->content.len = 1;
	token->type = type;
	return (offset);
}

// TODO: should i reference the token itself? since now i save the corresponding arena in the token?
void	grow_token(t_arena *arena, size_t idx)
{
	t_token	*token;

	printf("in arena_append_token at offset %zu\n", arena->offset);
	token = get_token_from_idx(arena, idx);
	++(token->content.len);
}

bool	is_op_char(char c)
{
	const char	*set = OPERATOR_SET;

	while (*set)
	{
		if (c == *set)
			return (true);
		++set;
	}
	return (false);
}

bool	is_op_str(char *c)
{
	const char	*operators[] = {"<<", ">>", "&&", "||", NULL};
	size_t	i;

	i = 0;
	while (operators[i])
	{
		if (!ft_strncmp(c, operators[i], 2))
			return (true);
		++i;
	}
	return (false);
}
