/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:39:35 by sancuta           #+#    #+#             */
/*   Updated: 2025/09/30 00:17:20 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;
	size_t	total_size;

	if (!nmemb || !size)
	{
		res = malloc(1);
		if (!res)
			return (NULL);
		ft_bzero(res, 1);
		return (res);
	}
	if (SIZE_MAX / size < nmemb)
	{
		return (NULL);
	}
	total_size = nmemb * size;
	res = malloc(total_size);
	if (!res)
		return (NULL);
	ft_bzero(res, total_size);
	return (res);
}
