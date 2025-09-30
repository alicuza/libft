/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 20:50:23 by sancuta           #+#    #+#             */
/*   Updated: 2025/09/29 21:24:09 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (*(unsigned char *)s++ && n-- >= 0)
		if (*(unsigned char *)s == (unsigned char)c)
			return ((void *)s);
	return (NULL);
}
