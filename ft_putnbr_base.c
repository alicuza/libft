/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:22:52 by sancuta           #+#    #+#             */
/*   Updated: 2025/07/31 12:55:14 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	is_base(char *base)
{
	int	i;
	int	j;
	int	len;

	len = ft_strlen(base);
	if (len < 2)
		return (0);
	i = 0;
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+')
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (len);
}

void	recurse(int nbr, char *base, int sign, int condition)
{
	int	base_len;

	base_len = ft_strlen(base);
	condition = nbr >= base_len;
	if (nbr < 0)
		condition = nbr <= -base_len;
	if (condition)
		recurse(nbr / base_len, base, sign, condition);
	ft_putchar(base[(nbr % base_len) * sign]);
}

void	ft_putnbr_base(int nbr, char *base)
{
	int	base_len;
	int	sign;
	int	condition;

	sign = 1;
	base_len = is_base(base);
	if (!base_len)
		return ;
	condition = nbr >= base_len;
	if (nbr < 0)
	{
		sign = -1;
		ft_putchar('-');
		condition = nbr <= -base_len;
	}
	recurse(nbr, base, sign, condition);
}
