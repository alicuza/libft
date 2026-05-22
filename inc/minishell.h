/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 21:48:28 by sancuta           #+#    #+#             */
/*   Updated: 2026/05/22 21:48:28 by sancuta          ###   ########.fr       */
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
  STRING,
  PROMPT,
  TOKEN,
  STACK,
  CMD,
  COUNT,
} t_arena_type;

typedef struct s_env
{
	char  	*read_line;
	t_arena	arena[5];
}	t_env;

#endif
