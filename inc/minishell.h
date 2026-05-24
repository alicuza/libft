/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 21:48:28 by sancuta           #+#    #+#             */
/*   Updated: 2026/05/24 02:24:54 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>				// printf, perror
# include <string.h>			// sterror
# include <readline/readline.h>	// readline, rl_clear_history, rl_on_new_line,
								// rl_replace_line, rl_redisplay
# include <readline/history.h>	// add_history
# include <stdlib.h>			// malloc, free, exit, getenv
# include <unistd.h>			// access, write, read, fork, dup, dup2, pipe,
								// getcwd, chdir, unlink, execve,
								// isatty, ttyname, ttyslot
# include <fcntl.h>				// open, close
# include <signal.h>			// signal, sigaction, sigemptyset, sigaddset,
								// kill
# include <dirent.h>			// opendir, readdir, closedir
# include <sys/wait.h>			// wait, waitpid, wait3, wait4
# include <sys/stat.h>			// stat, lstat, fstat
# include <sys/ioctl.h>			// ioctl
# include <termios.h>			// tcgetattr, tcsetattr
# include <termcap.h>			// tgetent, tgetflag, tgetnum, tgetstr, tgoto,
								// tputs

# include <stdint.h>			// TODO: consider for the saner type names

# include "libft.h"
# include "arena.h"

# ifdef DEBUG
#  include "debug.h"
# endif

typedef enum e_arena_type
{
	AT_STRING,
	AT_PROMPT,
	AT_TOKEN,
	AT_STACK,
	AT_CMD,
	AT_COUNT,
} t_arena_type;

typedef enum e_token_type
{
	TT_NONE,
	TT_WORD,
	TT_COUNT,
} t_token_type;

typedef struct s_ctx
{
	t_arena	arena[AT_COUNT];
	char  	*read_line;
}	t_ctx;

typedef struct s_slice
{
	size_t	start;
	size_t	len;
}	t_slice;

typedef struct s_token
{
	t_slice			content;
	t_token_type	type;
	size_t	next;
}	t_token;

#endif
