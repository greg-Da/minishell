/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:14:15 by dfeve             #+#    #+#             */
/*   Updated: 2024/11/11 14:22:12 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	int	i;

	i = 0;
	while (i < (int)n)
	{
		*(char *)(s + i) = (char)c;
		i++;
	}
	return (s);
}
/*
int main()
{
	char *test = malloc(10);
	ft_strlcpy(test, "hey", 3);
	printf("%s\n", test);
	ft_memset(test, 'c', 5);
	printf("%s\n", test);
}*/
