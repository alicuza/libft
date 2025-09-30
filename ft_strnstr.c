/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:34:38 by sancuta           #+#    #+#             */
/*   Updated: 2025/09/29 22:17:10 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((int)s1[i] - (int)s2[i]);
		i++;
	}
	return ((int)s1[i] - (int)s2[i]);
}

char	*strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (!ft_strlen(little))
		return ((char *)big);
	i = 0;
	while (i < len && big[i])
	{
		if (!ft_strcmp(big + i, little))
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
