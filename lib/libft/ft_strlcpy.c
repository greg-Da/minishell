/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:29:46 by dfeve             #+#    #+#             */
/*   Updated: 2024/11/11 15:20:09 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	int	i;

	i = 0;
	if (size <= 0)
		return (ft_strlen(src));
	while ((size_t)i < size - 1 && dst && src[i])
	{
		*(char *)(dst + i) = *(char *)(src + i);
		i++;
	}
	if (i == 0)
	{
		dst[i] = '\0';
		return (ft_strlen(src));
	}
	if (dst[i - 1])
		dst[i] = '\0';
	return (ft_strlen(src));
}
/*
int main()
{
	char	dstr[10] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 0};
	char	srcr[10] = {5, 5, 5, 0, 0, 0, 0, 0, 0, 0};

	printf("strlcpy returned %ld\n", ft_strlcpy(dstr, srcr, 5));
	for (int i = 0; i < 10; i++)
		printf("%d ", dstr[i]);
	printf("\n");
	char test[] = "caacaaa";
	char dst[] = "poopooo";
	char testy[] = "caacaaa";
	char dsty[] = "poopooo";	
	printf("%zu\n", ft_strlcpy(dst, test, 5));
	printf("%s\n", dst);
	printf("%zu\n", strlcpy(dsty, testy, 5));
	printf("%s\n", dsty);
}*/
