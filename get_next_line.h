/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:24:58 by sancuta           #+#    #+#             */
/*   Updated: 2025/11/21 13:25:00 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdlib.h>
# include <unistd.h>

typedef struct		s_stash
{
	ssize_t			len;
	ssize_t			offset;
	struct s_stash	*next;
	int				fd;
	char			content[BUFFER_SIZE + 1];
}					t_stash;

char	*get_next_line(int fd);
void	*ft_memset(void *s, int c, size_t n);
ssize_t	ft_indchr(const char *s, int c);
t_stash	*ft_bufnew(int fd);
t_stash	*ft_get_buffer_fd(t_stash **head, int fd);
char	*ft_join_to_del(char *nl_buf, t_stash *fd_buf, int del);
void	ft_free_buff();
#endif
