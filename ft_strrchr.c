/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 20:38:25 by sancuta           #+#    #+#             */
/*   Updated: 2025/10/06 22:01:38 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	size;

	size = ft_strlen(s);
	while (size > 0)
	{
		if ((int)s[size] == c)
			return (char *)s + size;
		size--;
	}
	if ((int)s[size] == c)
		return (char *)s + size;
	return (NULL);
}
