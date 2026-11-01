/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 09:33:17 by sancuta           #+#    #+#             */
/*   Updated: 2026/11/01 14:10:56 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_write(int fd, const char *s, t_write_type wt)
{
	ssize_t	ret;
	ssize_t	i;
	size_t	len;

	if (!s)
	{
		errno = EFAULT;
		return (-1);
	}
	len = 1;
	if (wt == WT_STR)
		len = ft_strlen(s);
	ret = 0;
	while ((size_t)ret < len)
	{
		errno = 0;
		i = write(fd, s + ret, len - ret);
		if (i > 0)
			ret += i;
		else if (errno != EINTR)
			return (-1);
	}
	return (ret);
}
