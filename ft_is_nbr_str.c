/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_nbr_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 02:08:10 by sancuta           #+#    #+#             */
/*   Updated: 2026/03/30 02:08:25 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_nbr_str(const char *nbr)
{
	int	i;

	i = 0;
	while (ft_isspace(nbr[i]))
		++i;
	if (ft_issign(nbr[i]))
		++i;
	if (!ft_isdigit(nbr[i]))
		return (0);
	while (nbr[i])
	{
		if (!ft_isdigit(nbr[i]))
			return (0);
		++i;
	}
	return (1);
}
