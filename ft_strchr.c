/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 20:01:12 by sancuta           #+#    #+#             */
/*   Updated: 2025/09/30 19:55:59 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	size;

	size = ft_strlen(s) + 1;
	while (size >= 0)
	{
		if ((int)*s == c)
			return ((char *)s);
		size--;
	}
	return (NULL);
}
