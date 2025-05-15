/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:12:23 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/20 15:40:23 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	printf("%d\n", strncmp("hello", "mello", 5));
	printf("%d\n", strncmp("ah", "ooh", 3));
	printf("%d\n", strncmp("aaa", "aaa", 3));
	printf("%d\n", ft_strncmp("hello", "mello", 5));
	printf("%d\n", ft_strncmp("ah", "ooh", 3));
	printf("%d\n", ft_strncmp("aaa", "aaa", 3));
}*/
