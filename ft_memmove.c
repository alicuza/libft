/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:38:23 by sancuta           #+#    #+#             */
/*   Updated: 2025/09/29 19:34:15 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest > src)
	{
		i = 0;
		while (i < n)
		{
			*((char *)dest + i) = *((const char *)src + i);
			i++;
		}
	}
	else
	{
		i = n - 1;
		while (i >= 0)
		{
			*((char *)dest + i) = *((const char *)src + i);
			i--;
		}
	}
	return (dest);
}
