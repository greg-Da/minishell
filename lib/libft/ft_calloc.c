/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:19:37 by dfeve             #+#    #+#             */
/*   Updated: 2024/11/14 17:35:19 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;

	if (size && nmemb > SIZEE_MAX / size)
		return (NULL);
	result = malloc(nmemb * size);
	if (!result)
		return (NULL);
	ft_bzero(result, size * nmemb);
	return (result);
}
/*
int main()
{
	int i;

	i = 0;
	int *test = ft_calloc(4, sizeof(int));
	while (i < 4)
	{
		printf("%d\n", test[i]);
		i++;
	}
}*/
