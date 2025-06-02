/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:37:29 by gdalmass          #+#    #+#             */
/*   Updated: 2025/05/21 14:55:46 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
		{
			in_word = 0;
		}
		s++;
	}
	return (count);
}

static size_t	ft_next_occurence(char const *s, char c, int index)
{
	while (s[index] && s[index] != c)
		index++;
	return ((size_t)index);
}

static char	**ft_free(char **arr, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		count;
	int		i;
	int		j;
	char	**arr;

	if (!s)
		return (NULL);
	i = 0;
	j = -1;
	count = ft_count_words(s, c);
	arr = malloc((count + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (++j < count)
	{
		while (s[i] == c)
			i++;
		arr[j] = ft_substr(s, (unsigned int)i, ft_next_occurence(s, c, i) - i);
		if (!arr[j])
			return (ft_free(arr, j));
		i += ft_next_occurence(s, c, i) - i;
	}
	arr[j] = NULL;
	return (arr);
}