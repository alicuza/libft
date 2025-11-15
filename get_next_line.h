/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:24:58 by sancuta           #+#    #+#             */
/*   Updated: 2025/11/15 09:30:31 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# include <stdlib.h>
# include <unistd.h>

typedef struct		s_stash
{
	ssize_t			len;
	struct s_stash	*next;
	int				fd;
	char			content[BUFFER_SIZE + 1];
}					t_stash;

#endif
