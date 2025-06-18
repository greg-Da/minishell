/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:37:29 by gdalmass          #+#    #+#             */
/*   Updated: 2025/06/18 12:50:49 by qbaret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_next_occurence(char *s, char c, int index)
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

static int	ft_fill_split(char **arr, char *s, char c, size_t limit)
{
	size_t	i;
	size_t	j;
	size_t	next;

	i = 0;
	j = 0;
	while (j < limit && s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		next = ft_next_occurence(s, c, i);
		arr[j] = ft_substr(s, (unsigned int)i, next - i);
		if (!arr[j++])
			return (-1);
		i = next;
	}
	while (s[i] == c)
		i++;
	arr[j] = ft_strdup(s + i);
	if (!arr[j])
		return (-1);
	arr[j + 1] = NULL;
	return (0);
}

char	**ft_nsplit(char *s, char c, size_t limit)
{
	char	**arr;

	if (!s)
		return (NULL);
	arr = malloc((limit + 2) * sizeof(char *));
	if (!arr)
		return (NULL);
	if (ft_fill_split(arr, s, c, limit) == -1)
		return (ft_free(arr, limit));
	return (arr);
}
