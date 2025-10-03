/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:01:28 by sancuta           #+#    #+#             */
/*   Updated: 2025/10/02 15:56:00 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char del)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != del && (i == 0 || s[i - 1] == del))
			count++;
		i++;
	}
	return (count);
}

static size_t	word_len(const char *s, char del)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != del)
		i++;
	return (i);
}

static char	**on_alloc_fail_free_str_arr(char **arr, size_t ind)
{
	while (ind > 0)
	{
		ind--;
		free(arr[ind]);
	}
	free(arr);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**res;
	size_t	i;
	size_t	word_nr;

	if (!s)
		return (NULL);
	word_nr = count_words(s, c);
	res = malloc((word_nr + 1) * sizeof (char *));
	if (!res)
		return (NULL);
	i = 0;
	while (i < word_nr)
	{
		while (!word_len(s, c))
			s++;
		res[i] = malloc((word_len(s, c) + 1) * sizeof (char));
		if (!res[i])
			return (on_alloc_fail_free_str_arr(res, i));
		ft_strlcpy(res[i], s, word_len(s, c) + 1);
		s += word_len(s, c);
		i++;
	}
	res[word_nr] = NULL;
	return (res);
}
