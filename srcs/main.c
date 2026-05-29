/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 21:47:55 by sancuta           #+#    #+#             */
/*   Updated: 2026/05/29 14:38:28 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ctx	init_ctx(void)
{
	t_ctx	c;

	ft_memset(&c, 0, sizeof(t_ctx));
	c.arena[AT_STRING] = arena_init(ARENA_SIZE, STR_SENTINEL_SIZE);
	c.arena[AT_PROMPT] = arena_init(ARENA_SIZE, STR_SENTINEL_SIZE);
	c.arena[AT_TOKEN] = arena_init(ARENA_SIZE, sizeof(t_token));
	return (c);
}

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;

	t_ctx	c;
#ifdef DEBUG
	size_t	cur_token_idx;
#endif

	c = init_ctx();
	while (true)
	{
		if (!get_user_input(&c))
			break ;
#ifdef DEBUG
		print_arena(&c.arena[AT_STRING]);
		while (true)
		{
			cur_token_idx = get_next_token_idx(&c);
			if (!cur_token_idx)
				break;
//			print_arena(&c.arena[AT_PROMPT]);
			print_token(&c, cur_token_idx);
			print_arena(&c.arena[AT_TOKEN]);
		}
#endif
		arena_reset(&c.arena[AT_STRING]);
		arena_clear(&c.arena[AT_TOKEN]);
	}
	return (0);
}
