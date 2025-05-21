/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:37:29 by gdalmass          #+#    #+#             */
/*   Updated: 2025/05/21 14:52:12 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static int	ft_count_words(char const *s, char c)
// {
// 	int	count;
// 	int	in_word;

// 	count = 0;
// 	in_word = 0;
// 	while (*s)
// 	{
// 		if (*s != c && !in_word)
// 		{
// 			in_word = 1;
// 			count++;
// 		}
// 		else if (*s == c)
// 		{
// 			in_word = 0;
// 		}
// 		s++;
// 	}
// 	return (count);
// }

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

char	**ft_nsplit(char const *s, char c, size_t limit)
{
	size_t	i;
	size_t	j;
	char	**arr;
	size_t	next;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	arr = malloc((limit + 2) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (j < limit && s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		next = ft_next_occurence(s, c, i);
		arr[j] = ft_substr(s, (unsigned int)i, next - i);
		if (!arr[j])
			return (ft_free(arr, j));
		i = next;
		j++;
	}
	while (s[i] == c)
		i++;
	arr[j] = ft_strdup((char *)(s + i));
	if (!arr[j])
		return (ft_free(arr, j));
	arr[j + 1] = NULL;
	return (arr);
}
