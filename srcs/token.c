/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 13:37:40 by sancuta           #+#    #+#             */
/*   Updated: 2026/05/26 00:01:03 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* TODO: could be part of a bigger function that also returns the length of the quoted text, if it is enclosed
 *       i would need to modify the grow function to take the length as a parameter
 *
 * int	get_quote_type(t_arena *input, size_t idx)
 * {
 * 	static int	quote_type; // TODO: figure out if i want the hassle of implementing the unenclosed quote as a char
 *
 * 	while (input->buf[idx] && !is_quote_char(input->buf[idx]))
 * 		++idx;
 * 	if (!input->buf[idx])
 * 		return (false);
 * 	return (true);
}
 */

size_t	get_next_token_idx(t_ctx *c, bool reset)
{
	static size_t	cur_char_idx;
	static size_t	cur_token_idx;
	t_arena			*input = &(c->arena[AT_STRING]); // TODO: think about making helper functions to return the arena by type
	t_arena			*tokens = &(c->arena[AT_TOKEN]);
	size_t			i;

	if (!cur_char_idx)
	{
		cur_char_idx = input->sentinel;
		cur_token_idx = 0;
	}
	printf("cur_char_idx: %c\n", input->buf[cur_char_idx]);
	printf("cur_char_idx: %s\n", input->buf + cur_char_idx);
	while (cur_char_idx <= input->offset)
	{
		if (input->buf[cur_char_idx] == '\0')	// rule 1
		{
			printf("rule 1\n");
/*			if (!cur_token_idx)	// TODO: need to consider if this is actually a good check for whether a token exists
 *			{
 *				cur_char_idx = 0;
 *				return (cur_token_idx);	// TODO: need to think about this more: returning 0 is saying that there was no token (it points to the sentinel), or that something went wrong
 *			}
 *			TODO: !! this is actually unnecessary, turns out the way i designed the arenas actually comes in handy here: the current index is returned either way
 */
			cur_char_idx = 0;
			return (cur_token_idx);
		}
		// TODO: figure out in general how this could be done better, if i want to use an unclosed quote as a char
		// 		also tracking of quotes is unnecessarym except for the case that a variable gets expanded to something
		// 		containing literal quotes
		else if (is_quote_char(input->buf[cur_char_idx] && is_enclosed_quote(input, cur_char_idx))		// rule 4
		{
			printf("rule 4\n");
			if (!cur_token_idx)
				cur_token_idx = get_idx_from_offset(tokens, start_token(tokens, cur_char_idx, TT_WORD));
			while (!is_quote_char(input->buf[cur_char_idx]))	// TODO: for now we iterate again over the quoted text and grow the token one by one
			{
				grow_token(tokens, cur_token_idx);	// TODO: should take length as a parameter to grow multiple times is necessary
				++cur_char_idx;
			}
			grow_token(tokens, cur_token_idx);	// TODO: would not be necessary if i implement growing the token by the len of the quoted section
			++cur_char_idx;
		}
		else if (token->type == TT_WORD) 		// rule 8
		{
			printf("rule 8\n");
			grow_token(tokens, cur_token_idx);
		}
												// rule 9 - being skipped
		else									// rule 10
		{
			printf("rule 10\n");
			cur_token_idx = get_idx_from_offset(tokens, start_token(tokens, cur_char_idx, TT_WORD));
		}
		++cur_char_idx;
	}
	return (cur_token_idx); // TODO: do i want it to return the byte offset or the array index?
}
