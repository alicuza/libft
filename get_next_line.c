/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:23:08 by sancuta           #+#    #+#             */
/*   Updated: 2025/11/21 13:25:49 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_stash	*head;
	t_stash			*buffer;
	char			*next_line;

	next_line = malloc(1);
	if (!next_line)
		return (NULL);
	ft_memset(next_line, 0, 1);
	buffer = ft_get_buffer_fd(&head, fd);
	if (!buffer)
		return (NULL);
	next_line = ft_join_to_del(next_line, buffer, '\n');
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
		if (!next_line)
			return (free(buffer), NULL); //TODO the bufferlist node needs to also be unlinked from the rest of the list
	}
	return (next_line);
}
