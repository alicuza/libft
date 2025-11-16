/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:23:08 by sancuta           #+#    #+#             */
/*   Updated: 2025/11/17 00:08:03 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

/*
	trigger for memory cleanup -> next read = 0, print old stuff out.
*/

void			*ft_memset(void *s, int c, size_t n);
ssize_t			ft_indchr(const char *s, int c);
static t_stash	*ft_bufnew(int fd);
static t_stash	*get_buffer_fd(t_stash **head, int fd);
static char		*ft_join_to_del(char *nl_buf, t_stash *fd_buf, int del);

char	*get_next_line(int fd)
{
	static t_stash	*head;
	t_stash			*buffer;
	char			*next_line;

	next_line = malloc(1);
	if (!next_line)
		return (NULL);
	ft_memset(next_line, 0, 1);
	buffer = get_buffer_fd(&head, fd);
	if (!buffer)
		return (NULL);
	next_line = ft_join_to_del(next_line, buffer, '\n');
	printf("DEBUG: offset=%ld, len=%ld, returned line=%s\n",
			buffer->offset, buffer->len, next_line);
	if (!next_line)
		return (NULL);
	while (ft_indchr(next_line, '\n') == -1)
	{
		if (buffer->len <= 0 || buffer->offset >= buffer->len)
		{
			ft_memset(buffer->content, 0, BUFFER_SIZE + 1);
			buffer->len = read(buffer->fd, buffer->content, BUFFER_SIZE);
			if (buffer->len <= 0)
				return (free(buffer), NULL);
			buffer->offset = 0;
		}
		next_line = ft_join_to_del(next_line, buffer, '\n');
		printf("DEBUG: offset=%ld, len=%ld, returned line=%s\n",
				buffer->offset, buffer->len, next_line);
		if (!next_line)
			return (free(buffer), NULL);	//TODO the bufferlist node needs to also be unlinked from the rest of the list
	}
	return (next_line);
}

static t_stash	*ft_bufnew(int fd)
{
	t_stash	*new;

	new = malloc(sizeof(t_stash));
	if (!new)
		return (NULL);
	ft_memset(new, 0, sizeof(t_stash));
	new->fd = fd;
	new->len = read(fd, new->content, BUFFER_SIZE);
	if (new->len <= 0)
		return (free(new), NULL);
	new->next = NULL;
	return (new);
}

static t_stash	*get_buffer_fd(t_stash **head, int fd)
{
	t_stash	*buffer;

	if (!(*head))
	{
		*head = ft_bufnew(fd);
		if (!(*head))
			return (NULL);
		return (*head);
	}
	buffer = *head;
	while (buffer)
	{
		if (buffer->fd == fd)
			return (buffer);
		if (!buffer->next)
		{
			buffer->next = ft_bufnew(fd);
			if (!buffer->next)
				return (NULL);
			return (buffer->next);
		}
		buffer = buffer->next;
	}
	return (NULL);
}

static char	*ft_join_to_del(char *nl_buf, t_stash *fd_buf, int del)
{
	size_t	i;
	size_t	j;
	size_t	nl_len;
	size_t	buf_len;
	char	*tmp;

	tmp = NULL;
	nl_len = 0;
	while (nl_buf[nl_len])
		nl_len++;
	buf_len = 0;
	while (*(fd_buf->content + fd_buf->offset + buf_len)
			&& *(fd_buf->content + fd_buf->offset + buf_len) != del)
		buf_len++;
	if (*(fd_buf->content + fd_buf->offset + buf_len) == del)
		buf_len++;
	tmp = malloc(nl_len + buf_len + 1);
	if (!tmp)
		return (free(nl_buf), NULL);
	ft_memset(tmp, 0, nl_len + buf_len + 1);
	i = 0;
	while (i < nl_len)
	{
		tmp[i] = nl_buf[i];
		i++;
	}
	j = 0;
	while (j < buf_len)
	{
		tmp[i] = *(fd_buf->content + fd_buf->offset);
		i++;
		j++;
		fd_buf->offset++;
	}
	return (free(nl_buf), tmp);
}
