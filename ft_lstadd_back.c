/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:20:31 by sancuta           #+#    #+#             */
/*   Updated: 2026/11/01 13:52:31 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *node)
{
	if (!(node && lst))
		return ;
	if (!*lst)
	{
		*lst = node;
		return ;
	}
	ft_lstlast(*lst)->next = node;
}
