/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:18:29 by sancuta           #+#    #+#             */
/*   Updated: 2025/10/27 12:49:45 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	int c = -1;
	char s[4];

	while (++c < 256)
	{
		sprintf(s, "%d", c);
		write(1, s, strlen(s));
		write(1, ": ", 2);
		write(1, &c, 1);
		write(1, "\n", 1);
	}
	return 0;
}
