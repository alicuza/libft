/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 14:48:25 by sancuta           #+#    #+#             */
/*   Updated: 2025/11/21 13:25:27 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((unsigned char *)s + i) = (unsigned char) c;
		i++;
	}
	return (s);
}

ssize_t	ft_indchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((ssize_t)i);
		i++;
	}
	if ((unsigned char)s[i] == (unsigned char)c)
		return ((ssize_t)i);
	return (-1);
}

t_stash	*ft_bufnew(int fd)
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

t_stash	*ft_get_buffer_fd(t_stash **head, int fd)
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

char	*ft_join_to_del(char *nl_buf, t_stash *fd_buf, int del)
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
