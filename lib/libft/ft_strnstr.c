/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:18:16 by dfeve             #+#    #+#             */
/*   Updated: 2024/11/13 21:12:53 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int	i;

	i = 0;
	if (len > ft_strlen(big))
		len = ft_strlen(big);
	if (little[i] == '\0')
		return ((char *)big);
	if (big[i] == '\0')
		return (NULL);
	while (i < (int)len)
	{
		if (big[i] == little[0] && (i + ft_strlen(little)) <= len)
		{
			if (ft_strncmp(big + i, little, ft_strlen(little)) == 0)
			{
				return ((char *)(big + i));
			}
		}
		i++;
	}
	return (NULL);
}
/*
int main()
{
	printf("%s\n", ft_strnstr("Tro", "tombola", 20));
	printf("%s\n", strnstr("Tr", "tombola", 20));
}*/
