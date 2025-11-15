/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 14:48:25 by sancuta           #+#    #+#             */
/*   Updated: 2025/11/13 15:17:21 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_str_to_next_del(t_stash buffer, int del)
{
	int		i;
	char	*ret;

	while (i < buffer.len)
		if(s[i] == del)
			ret = malloc((i + 1) * sizeof(char));
		i++;
	ret = malloc((i + 1) * sizeof(char));
	if (!ret)
		return (NULL);






}
