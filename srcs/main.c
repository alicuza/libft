/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 21:47:55 by sancuta           #+#    #+#             */
/*   Updated: 2026/05/25 17:26:24 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

t_ctx	init_ctx(void)
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
	size_t	cur_token_idx;

	c = init_ctx();
	while (true)
	{
		if (!get_user_input(&c))
			break ;
		cur_token_idx = get_next_token_idx(&c);
#ifdef DEBUG
//		print_arena(&c.arena[AT_PROMPT]);
		print_arena(&c.arena[AT_STRING]);
		print_arena(&c.arena[AT_TOKEN]);
		print_token(&c, cur_token_idx);
#endif
		arena_reset(&c.arena[AT_STRING]);
		arena_reset(&c.arena[AT_TOKEN]);
	}
	return (0);
}
