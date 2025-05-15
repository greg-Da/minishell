/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:39:34 by dfeve             #+#    #+#             */
/*   Updated: 2024/11/11 14:25:21 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*result;
	int		i;

	i = 0;
	result = NULL;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			result = (char *)s + i;
		i++;
	}
	if (s[i] == (char)c)
		result = (char *)s + i;
	return (result);
}
/*
int main()
{
	char *test = "hello";
	printf("%s\n", ft_strrchr(test, '\0'));
	char *testi = "hello";
	printf("%s\n", strrchr(testi, '\0'));
}*/
