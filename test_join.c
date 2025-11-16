#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

char *ft_join_to_del(char *nl_buf, t_stash *fd_buf, int del)
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
	while (*(fd_buf->content + BUFFER_SIZE - fd_buf->len + 1 + i))
	{
		if (*(fd_buf->content + BUFFER_SIZE - fd_buf->len + 1 + i) == del)
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
	memset(tmp, 0, nl_len + buf_len + 1);
	i = 0;
	while (i < nl_len)
	{
		tmp[i] = nl_buf[i];
		i++;
	}
	i = 0;
	while (i < buf_len)
	{
		tmp[nl_len + i] = *(fd_buf->content + BUFFER_SIZE - fd_buf->len + 1 + i);
		i++;
	}
	return (free(nl_buf), tmp);
}

int	main(void)
{
	t_stash	buffer;
	memset(&buffer, 0, sizeof(t_stash));
	memcpy(buffer.content, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0ich bin ein berliner.\n", sizeof(buffer.content));
	buffer.len = 23;
//	char line2[23] = "ich esse\ngerne\nkacke\n\n";
	char *nlb1 = malloc(10);
	memset(nlb1, 0, 10);
	strcpy(nlb1, " ");
/*	char *nlb2 = malloc(5);
	memset(nlb2, 0, 5);
	char *nlb3 = malloc(15);
	memset(nlb3, 0, 15);
	char *nlb4 = malloc(23);
	memset(nlb3, 0, 23);
*/	
	printf("1: %s\n", ft_join_to_del(nlb1, &buffer, '\n'));
	return (0);
}
