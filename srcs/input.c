/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 12:45:50 by sancuta           #+#    #+#             */
/*   Updated: 2026/05/25 13:57:34 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_user_input(t_ctx *c)
{
	size_t	offset;

	c->read_line = readline(get_prompt(c));
	if (!c->read_line)
		return (0);
	if (*(c->read_line))
		add_history(c->read_line);
	offset =
		arena_strlcpy(&(c->arena[AT_STRING]), c->read_line, ft_strlen(c->read_line) + 1);
	// TODO: this should be implemented to concatenate the here_doc lines together until i find the `eoi/eof`
	//	arena_strlcat(&(c->arena[AT_STRING]), "\n", 2);
	free(c->read_line);
	return (offset);
}
