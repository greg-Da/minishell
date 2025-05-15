/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:22:12 by dfeve             #+#    #+#             */
/*   Updated: 2024/11/11 14:23:26 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *str, int sechar)
{
	char	*result;
	int		i;

	i = 0;
	result = NULL;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == (char)sechar)
		{
			result = (char *)(str + i);
			break ;
		}
		i++;
	}
	if (str[i] == (char)sechar)
		result = (char *)(str + i);
	return (result);
}
/*
int main()
{
	printf("%s", ft_strchr("tripouille", 't' + 256));
}*/
