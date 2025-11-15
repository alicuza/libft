/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:23:08 by sancuta           #+#    #+#             */
/*   Updated: 2025/11/15 21:55:26 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
	trigger for memory cleanup -> next read = 0, print old stuff out.
*/

char	*get_next_line(int fd)
{
	static t_stash	**head;
	t_stash			*buffer;
	char			*next_line;
	char			tmp[BUFFER_SIZE + 1];

	buffer = get_buffer_fd(*head, fd);
	if (!buffer)
		return (NULL); // EXPLAIN: we don't want to free in case of failure, otherwise we lose the state of our position in the other fd, which should not be affected by failure here.
	next_line = get_next(buffer, next_line); //NOTE: can I handle some more logic in this top level function, and help shorten get_next()?
	if (!next_line)
		return (NULL);
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
		return (NULL);
	new->next = NULL;
	return (new);
}

static t_stash	*get_buffer_fd(t_stash **head, int fd)
{
	t_stash	*buffer;

	buffer = *head;
	if (!buffer)
	{
		buffer = ft_bufnew(fd);
		if (!buffer)
			return (NULL);
		return (buffer)
	}
	while (buffer)
	{
		if (buffer->fd == fd)
			return (buffer);
		buffer = buffer->next;
	}
	buffer = ft_bufnew(fd);
	if (!buffer)
		return (NULL);
	return (buffer)
}

static char	*get_next(t_stash *buffer, char *next_line_buffer)
{
	char	*nl_pos;

	nl_pos = ft_strchr(buffer->content, '\n'); //TODO: decide whether to keep strchr or implement something else instead
	while (!nl_pos)
	{
		if (buffer->len = 0)
		{
			ft_memset(buffer->content, 0, BUFFER_SIZE);
			buffer->len = read(buffer->fd, buffer->content, BUFFER_SIZE);
			if (buffer->len == -1)
				return (free(buffer), NULL);
			else if (buffer->len == 0)
				return (free(buffer), next_line_buffer);
		}
		next_line_buffer = ft_join_to_del(next_line_buffer, buffer); //NOTE: join_to_del should handle NULL inputs as empty strings. also, this way it would leak memory by not freeing the last next_line_buffer that was merged into this new one -> be sure to handle that case in ft_join_to_del
		if (!next_line_buffer)
			return (NULL); //TODO: figure out if and how to handle freeing here
		buffer->len = 0;
		nl_pos = ft_strchr(buffer->content, '\n');
	}
	next_line_buffer = ft_join_to_del(next_line_buffer, buffer);
	if (!next_line_buffer)
		return (NULL); //TODO: figure out how to handle freeing
	return (next_line_buffer);
}

static char *ft_join_to_del(char *nl_buf, t_stash *fd_buf, char del)
{
	size_t	i;
	size_t	nl_len;
	size_t	buf_len;
	char	*tmp;

	tmp = nl_buf;
	i = 0;
	while (nl_buf[i])
		i++;
	nl_len = i;
	i = 0;
	while (*(fd_buf->content + BUFFER_SIZE - fd_buf->len + i))
	{
		if (*(fd_buf->content + BUFFER_SIZE - fd_buf->len + i) == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	buf_len = i;
	tmp = malloc(nl_len + buf_len + 1);
	if (!tmp)
		return (free(nl_buf), NULL);
	ft_memset(tmp, 0, nl_len + buf_len + 1)
	i = 0;
	while (i < nl_len)
	{
		tmp[i] = nl_buf[i];
		i++;
	}
	free(nl_buf);
	i = 0;
	while (i < buf_len)
	{
		tmp[nl_len + i] = *(fd_buf->content + BUFFER_SIZE - fd_buf->len + i);
		i++;
	}
	return (free(nl_buf), tmp);
}

/*
	if (!(*nl_buf) && !(*fd_buf->content))
	{
		ret = malloc(1);
		if (!ret)
			return (NULL);
		ft_memset(ret, 0, 1);
		return (ret);
	}
	if (!(*fd_buf->content))
		return (nl_buf);
	if (!(*nl_buf))
	{
		
		return ();
	}
*/

/* not necessary, if i modify join_to_del to join up to '\0' or '\n'

	nl_pos = ft_strchr(buffer->content, '\n');
	if (nl_pos)
	{
		tmp = memset(tmp, 0, BUFFER_SIZE + 1);
		tmp = ft_strlcpy(tmp, buffer->content + (BUFFER_SIZE - buffer->len), nl_pos - (BUFFER_SIZE - buffer->len));
		ft_memset(buffer->content + (BUFFER_SIZE - buffer->len), nl_pos - (BUFFER_SIZE - buffer->len));
		buffer->len = BUFFER_SIZE - nl_pos;
		return (ft_join_to_del(next_line, tmp)); // TODO adjust join_to_del to not just stop at '\0', but also after '\n', then i can skip the `if (nl_pos)` stuff;
	}
*/
