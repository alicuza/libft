/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 12:41:14 by sancuta           #+#    #+#             */
/*   Updated: 2026/05/30 18:25:52 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define GREEN "\033[38;5;40m"
#define RESET "\033[0m"

char	*get_prompt(t_ctx *c)
{
	size_t	offset;
	size_t	tmp_offset;
	t_arena	*prompt;

	prompt = &(c->arena[AT_PROMPT]);
	arena_reset(prompt);
	offset = arena_strlcpy(prompt, GREEN, ft_strlen(GREEN) + 1);
	arena_strlcat(prompt, getenv("USER"), ft_strlen(getenv("USER")) + 1); // TODO: this seems to not work correctly, i probably need strlen + 1
	arena_strlcat(prompt, "@", 2);
	arena_strlcat(prompt, "shni", 5);
	arena_strlcat(prompt, ":", 2);
	tmp_offset = arena_alloc(prompt, CWD_SIZE, 1);
	getcwd(prompt->buf + tmp_offset - 1, CWD_SIZE); // TODO: is there a better way of doing this?
	prompt->offset =
		prompt->sentinel + ft_strlen(prompt->buf + prompt->sentinel) + 1;
	arena_strlcat(prompt, "$ ", 3);
	arena_strlcat(prompt, RESET, ft_strlen(RESET) + 1);
	return ((char *)get_arena_ptr(prompt, offset));
}
