/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 21:47:55 by sancuta           #+#    #+#             */
/*   Updated: 2026/05/24 02:24:52 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

#ifndef ARENA_SIZE
# define ARENA_SIZE 64
#endif
#define CWD_SIZE 256
#define STR_SENTINEL_SIZE 1
#define NO_TOKEN 0

// TODO: consider using static variables to simplify managing the arenas.
char	*ft_get_prompt(t_ctx *c)
{
	size_t	offset;
	size_t	tmp_offset;
	t_arena	*prompt;

	prompt = &(c->arena[AT_PROMPT]);
	arena_reset(prompt);
	offset = arena_strlcpy(prompt, getenv("USER"), ft_strlen(getenv("USER")) + 1); // TODO: this seems to not work correctly, i probably need strlen + 1
	arena_strlcat(prompt, "@", 2);
	arena_strlcat(prompt, "fanish", 7);
	arena_strlcat(prompt, ":", 2);
	tmp_offset = arena_alloc(prompt, CWD_SIZE, 1);
	getcwd(prompt->buf + tmp_offset - 1, CWD_SIZE); // TODO: is there a better way of doing this?
	prompt->offset =
		prompt->sentinel + ft_strlen(prompt->buf + prompt->sentinel) + 1;
	arena_strlcat(prompt, "$ ", 3);
	return ((char *)get_arena_ptr(prompt, offset));
}

size_t	ft_get_user_input(t_ctx *c)
{
	size_t	offset;

	c->read_line = readline(ft_get_prompt(c));
	if (!c->read_line)
		return (0);
	if (*(c->read_line))
		add_history(c->read_line);
	offset =
		arena_strlcpy(&(c->arena[AT_STRING]), c->read_line, ft_strlen(c->read_line) + 1);
	//	arena_strlcat(&(c->arena[AT_STRING]), "\n", 2); // TODO: this should be implemented to concatenate the here_doc lines together until i find the `eoi/eof`
	free(c->read_line);
	return (offset);
}

t_ctx	init_ctx(void)
{
	t_ctx	c;

	ft_memset(&c, 0, sizeof(t_ctx));
	c.arena[AT_STRING] = arena_init(ARENA_SIZE, STR_SENTINEL_SIZE);
	c.arena[AT_PROMPT] = arena_init(ARENA_SIZE, STR_SENTINEL_SIZE);
	c.arena[AT_TOKEN] = arena_init(ARENA_SIZE, sizeof(t_token));
	return (c);
}

size_t	arena_start_token(t_ctx *c, size_t start, t_token_type type)
{
	t_arena	*arena;
	t_token	*token;
	size_t offset;

	arena = &(c->arena[AT_TOKEN]);
	offset = arena_alloc(arena, sizeof(t_token), _Alignof(t_token));
	printf("in arena_start_token at offset %zu\n", offset);
	token = (t_token *)(arena->buf + offset); // TODO: maybe as function? can imagine it would help in a lot of places
	token->content.start = start;
	token->content.len = 1;
	token->type = type;
	return (offset);
}

void	arena_append_token(t_ctx *c, size_t id)
{
	t_arena	*arena;
	t_token	*token;

	arena = &(c->arena[AT_TOKEN]);
	token = (t_token *)(arena->buf + id);
	++(token->content.len);
}

size_t get_next_token(t_ctx *c)
{
	static size_t	cur_c;
	t_arena			*input = &(c->arena[AT_STRING]);
	t_arena			*tokens = &(c->arena[AT_TOKEN]);
	t_token			*token;
	size_t			offset;

	token = (t_token *)(tokens->buf + tokens->offset);
	offset = 0;
	if (!cur_c)
		cur_c = input->sentinel;
	printf("cur_c: %c\n", input->buf[cur_c]);
	printf("cur_c: %s\n", input->buf + cur_c);
	while (cur_c <= input->offset)
	{
		if (input->buf[cur_c] == '\0')	// rule 1
		{
			printf("rule 1\n");
			if (!token->type)	// TODO: need to consider if this is actually a good check for whether a token exists
				return (++cur_c, NO_TOKEN);	// TODO: need to think about this more: returning 0 is saying that there was no token (it points to the sentinel), or that something went wrong
			return (++cur_c, tokens->offset);
		}
		else if (token->type == TT_WORD) // rule 8, we are skipping 9 for now
		{
			printf("rule 8\n");
			arena_append_token(c, offset);
		}
		else	// rule 10
		{
			printf("rule 10\n");
			offset = arena_start_token(c, cur_c, TT_WORD);
		}
		++cur_c;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;

	t_ctx	c;

	c = init_ctx();
	while (ft_get_user_input(&c))
	{
		get_next_token(&c);
#ifdef DEBUG
		print_arena(&c.arena[AT_STRING]);
		//		print_arena(&c.arena[AT_PROMPT]);
		print_arena(&c.arena[AT_TOKEN]);
#endif
	}
	return (0);
}
