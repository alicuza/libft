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
#define ARENA_SIZE 256
#define CWD_SIZE 256

char	*ft_get_prompt()
{
	char	*prompt;
	char	cwd[CWD_SIZE];

	prompt = ft_strjoin(getenv("USER"), "@");
	prompt = ft_strjoin(prompt, getcwd(cwd, CWD_SIZE));
	prompt = ft_strjoin(prompt, "$ ");
	//TODO: error handling
	return (prompt);
}

char	*ft_get_user_input(void)
{
	static char	*buffer;

	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}
	buffer = readline(ft_get_prompt());
	if (buffer && *buffer)
		add_history(buffer);

	return (buffer);
}

int	main(int argc, char **argv, char **envp)
{
	(void)	argc;
	(void)	argv;
	(void)	envp;

/*	t_env	env;

	env->prompt = arena_init(ARENA_SIZE);
*/

	while (ft_get_user_input())
		;
	return (0);
}
