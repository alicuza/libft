/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 13:41:30 by sancuta           #+#    #+#             */
/*   Updated: 2026/05/08 12:25:43 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ARENA_SIZE 1024
#define CWD_SIZE 256
#define STR_SENTINEL_SIZE 1


// TODO: consider using static variables to simplify managing the arenas.
char	*ft_get_prompt(t_env *e)
{
	size_t	offset;
	t_arena	prompt;

	prompt = arena_init(CWD_SIZE, STR_SENTINEL_SIZE);
	offset = arena_strlcpy(&prompt, getenv("USER"), ft_strlen(getenv("USER")));
	arena_strlcpy(&prompt, "@", 1);
	getcwd(prompt.buf + prompt.offset, CWD_SIZE); // TODO: is there a better way of doing this?
	prompt.offset = prompt.sentinel + ft_strlen(prompt.buf + prompt.sentinel);
	arena_strlcpy(&prompt, "$ ", 2);
	return ((char *)get_arena_ptr(&prompt, offset));
}

size_t	ft_get_user_input(t_env *e)
{
	size_t	offset;

	e->read_line = readline(ft_get_prompt(e->prompt));
	// TODO: error management for failing readline
	if (e->read_line && *(e->read_line))
		add_history(e->read_line);
	offset = arena_strlcpy(e->strings, e->read_line, ft_strlen(e->read_line));
	free(readline);
	return (offset);
}

t_env	init_env()
{
	t_env	env;

	return (env);
}
int	main(int argc, char **argv, char **envp)
{
	(void)	argc;
	(void)	argv;
	(void)	envp;

	t_env	env;
	t_arena	strings;

	strings = arena_init(ARENA_SIZE, STR_SENTINEL_SIZE);
	env.strings = strings;
	ft_get_user_input(&env, &strings);
	while (env.strings->offset)
		ft_get_user_input(&env);
	return (0);
}
