/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 13:37:40 by sancuta           #+#    #+#             */
/*   Updated: 2026/05/25 17:13:41 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_next_token_idx(t_ctx *c)
{
	static size_t	cur_char_id;
	static size_t	cur_token_id;
	t_arena			*input = &(c->arena[AT_STRING]); // TODO: think about making helper functions to return the arena by type
	t_arena			*tokens = &(c->arena[AT_TOKEN]);
	t_token			*token;

	token = (t_token *)(tokens->buf);
	if (!cur_char_id)
	{
		cur_char_id = input->sentinel;
		cur_token_id = 0;
	}
	printf("cur_char_id: %c\n", input->buf[cur_char_id]);
	printf("cur_char_id: %s\n", input->buf + cur_char_id);
	while (cur_char_id <= input->offset)
	{
		if (input->buf[cur_char_id] == '\0')	// rule 1
		{
			printf("rule 1\n");
			if (!token->type)	// TODO: need to consider if this is actually a good check for whether a token exists
			{
				cur_char_id = 0;
				return (NO_TOKEN);	// TODO: need to think about this more: returning 0 is saying that there was no token (it points to the sentinel), or that something went wrong
			}
			cur_char_id = 0;
			return (cur_token_id);
		}
		else if (token->type == TT_WORD) // rule 8, we are skipping 9 for now
		{
			printf("rule 8\n");
			grow_token(tokens, cur_token_id);
		}
		else	// rule 10
		{
			printf("rule 10\n");
			cur_token_id = get_idx_from_offset(tokens, start_token(tokens, cur_char_id, TT_WORD));
			token++;
		}
		++cur_char_id;
	}
	return (cur_token_id); // TODO: do i want it to return the byte offset or the array index?
}
