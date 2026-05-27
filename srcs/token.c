/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 13:37:40 by sancuta           #+#    #+#             */
/*   Updated: 2026/05/27 15:05:25 by sancuta          ###   ########.fr       */
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
/* TODO: might be unnecessary
 *
 * bool	is_enclosed_quote(t_arena *input, size_t idx)
 * {
 * 	char	quote;
 * 
 * 	if (is_char_in_set(input->buf[cur_char_idx], QUOTE_SET))
 * 	{
 * 		quote = input->buf[idx];
 * 		++idx;
 * 	}
 * 	while (input->buf[idx] && input->buf[idx] != quote)
 * 		++idx;
 * 	if (!input->buf[idx])
 * 		return (false);
 * 	return (true);
 * }
 */ 
// returns the passed cur_char_idx or the updated one, if the quote is closed
static size_t	try_as_enclosed_quote(t_ctx *c, size_t token_idx, size_t input_idx)
{
	size_t	saved_len;	// TODO: could add this offset variable as static in the arena function itself.
	size_t	new_input_idx;
	t_arena	*input = &(c->arena[AT_STRING]);
	t_arena	*tokens = &(c->arena[AT_TOKEN]);

	new_input_idx = input_idx + 1;
	saved_len = save_token_len(get_token_from_idx(tokens, token_idx)); // TODO: arena_save is not the correct function for this.
	while (input->buf[new_input_idx] && (input->buf[new_input_idx] != input->buf[input_idx]))
	{
		grow_token(tokens, token_idx);
		++new_input_idx;
	}
	if (!input->buf[new_input_idx])
	{
		restore_token_len(get_token_from_idx(tokens, token_idx), saved_len);
		return (input_idx);
	}
	grow_token(tokens, token_idx);
	return (new_input_idx);
}

// TODO: !!NOW: figure out how to actually implement the blanks
size_t	get_next_token_idx(t_ctx *c)
{
	static size_t	cur_char_idx;
	static size_t	cur_token_idx;
	t_arena			*input = &(c->arena[AT_STRING]); // TODO: think about making helper functions to return the arena by type
	t_arena			*tokens = &(c->arena[AT_TOKEN]);

	if (!cur_char_idx)
	{
		cur_char_idx = input->sentinel;
		cur_token_idx = 0;
	}
#ifdef DEBUG
	printf("cur_char_idx: %c\n", input->buf[cur_char_idx]);
	printf("cur_char_idx: %s\n", input->buf + cur_char_idx);
#endif
	while (cur_char_idx <= input->offset)
	{
		if (input->buf[cur_char_idx] == '\0')	// rule 1
		{
#ifdef DEBUG
			printf("rule 1\n");
#endif
			cur_char_idx = 0;
			return (cur_token_idx);
		}
		// TODO: figure out in general how this could be done better, if i want to use an unclosed quote as a char
		// 		also tracking of quotes is unnecessarym except for the case that a variable gets expanded to something
		// 		containing literal quote chars
		else if (is_char_in_set(input->buf[cur_char_idx], QUOTE_SET))		// rule 4
		{
#ifdef DEBUG
			printf("rule 4\n");
#endif
			if (!cur_token_idx)
				cur_token_idx = get_idx_from_offset(tokens, start_token(tokens, cur_char_idx, TT_WORD));
			else
				grow_token(tokens, cur_token_idx);
			cur_char_idx = try_as_enclosed_quote(c, cur_token_idx, cur_char_idx);
 		}
		else if (is_char_in_set(input->buf[cur_char_idx], BLANK_SET))		// rule 7
		{
			++cur_char_idx;
			return (cur_token_idx++);
		}
		else if (get_token_from_idx(tokens, cur_token_idx)->type == TT_WORD) 		// rule 8
		{
#ifdef DEBUG
			printf("rule 8\n");
#endif
			grow_token(tokens, cur_token_idx);
		}
												// rule 9 - being skipped
		else									// rule 10
		{
#ifdef DEBUG
			printf("rule 10\n");
#endif
			cur_token_idx = get_idx_from_offset(tokens, start_token(tokens, cur_char_idx, TT_WORD));
		}
		++cur_char_idx;
	}
	return (0); // TODO: do i want it to return the byte offset or the array index?
}
