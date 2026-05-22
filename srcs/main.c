/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 21:47:55 by sancuta           #+#    #+#             */
/*   Updated: 2026/05/22 21:56:33 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

#define ARENA_SIZE 64
#define CWD_SIZE 256
#define STR_SENTINEL_SIZE 1

// TODO: consider using static variables to simplify managing the arenas.
char	*ft_get_prompt(t_env *e)
{
	size_t	offset;
	t_arena	*prompt;

	prompt = &(e->arena[PROMPT]);
	arena_reset(prompt);
	offset = arena_strlcpy(prompt, getenv("USER"), ft_strlen(getenv("USER")) + 1); // TODO: this seems to not work correctly, i probably need strlen + 1
	arena_strlcat(prompt, "@", 2);
	arena_strlcat(prompt, "fanish", 7);
	arena_strlcat(prompt, ":", 2);
	getcwd(prompt->buf + prompt->offset - 1, CWD_SIZE); // TODO: is there a better way of doing this?
	prompt->offset =
		prompt->sentinel + ft_strlen(prompt->buf + prompt->sentinel) + 1;
	arena_strlcat(prompt, "$ ", 3);
	return ((char *)get_arena_ptr(prompt, offset));
}

size_t	ft_get_user_input(t_env *e)
{
	size_t	offset;

	e->read_line = readline(ft_get_prompt(e));
	if (!e->read_line)
		return (0);
	if (*(e->read_line))
		add_history(e->read_line);
	offset =
		arena_strlcpy(&(e->arena[STRING]), e->read_line, ft_strlen(e->read_line) + 1);
	arena_strlcat(&(e->arena[STRING]), "\n", 2);
	free(e->read_line);
	return (offset);
}

t_env	init_env(void)
{
	t_env	env;

	ft_memset(&env, 0, sizeof(t_env));
	env.arena[STRING] = arena_init(ARENA_SIZE, STR_SENTINEL_SIZE);
	env.arena[PROMPT] = arena_init(ARENA_SIZE, STR_SENTINEL_SIZE);
	//	env.arena[TOKEN] = arena_init(ARENA_SIZE, sizeof(t_token));
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;

	t_env	env;

	env = init_env();
	ft_get_user_input(&env);
#ifdef DEBUG
	print_arena(&env.arena[STRING]);
#endif
	while (ft_get_user_input(&env))
	{
#ifdef DEBUG
		print_arena(&env.arena[STRING]);
#endif
	}
	return (0);
}
