/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:08:05 by dfeve             #+#    #+#             */
/*   Updated: 2024/11/11 16:57:45 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int		i;
	int		c;
	size_t	dlen;

	i = 0;
	c = 0;
	dlen = ft_strlen(dst);
	while (dst[i])
		i++;
	while (src[c] && ((size_t)i + 1) < size)
	{
		dst[i] = src[c];
		c++;
		i++;
	}
	if ((size_t)i < size)
		dst[i] = '\0';
	if (size <= dlen)
		return (ft_strlen(src) + size);
	else
		return (ft_strlen(src) + dlen);
}
/*
int main()
{
	char *test = malloc(15);
	ft_memset(test, 0, 15);
	ft_memset(test, 'r', 15);
	char *ti = "lorem ipsum dolor sit amet";
	printf("%zu\n", ft_strlcat(test, ti, 0));
	printf("%s\n", test);
	char *testi = malloc(15);
	ft_memset(testi, 0, 15);
	ft_memset(testi, 'r', 15);
	char *tii = "lorem ipsum dolor sit amet";
	printf("%zu\n", strlcat(testi, tii, 0));
	printf("%s\n", testi);
}*/
