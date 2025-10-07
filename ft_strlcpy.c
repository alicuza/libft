/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:01:58 by sancuta           #+#    #+#             */
/*   Updated: 2025/10/07 18:39:59 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
//	size_t	src_len;

	if (!size)
		return (ft_strlen(src));
	i = 0;
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	char *buffer = calloc(101, 1);
	char *dst = buffer + 20;
	const char *src_before = buffer + 10;
	const char *src_after = buffer + 40;
	size_t size = 30;

	int i = 0;
	while (i < 20)
		buffer[i++] = 'a';
	while (i < 40)
		buffer[i++] = 'b';
	while (i < 60)
		buffer[i++] = 'c';
	while (i < 80)
		buffer[i++] = 'd';
	while (i < 100)
		buffer[i++] = 'e';
	printf("before function:\n");
	printf("buffer = %s\n", buffer);
	printf("dest = %s\n", dst);
	printf("src_before = %s\n", src_before);
	printf("src_after = %s\n", src_after);
	printf("return ft_strlcpy = %zu\n", ft_strlcpy(dst, src_before, size));
	printf("after function:\n");
	printf("buffer = %s\n", buffer);
	printf("dest = %s\n", dst);
	printf("src_before = %s\n", src_before);
	printf("src_after = %s\n", src_after);
}
