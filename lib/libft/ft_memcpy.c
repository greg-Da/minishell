/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:23:35 by dfeve             #+#    #+#             */
/*   Updated: 2024/11/15 19:27:24 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int	i;

	i = 0;
	while (i < (int)n)
	{
		*(char *)(dest + i) = *(char *)(src + i);
		i++;
	}
	return (dest);
}
/*
int main()
{
	char *dest = malloc(5);
	char *src = "hey";
	printf("%s\n", (char *)ft_memcpy(NULL, NULL, 3));
	free(dest);
}*/
