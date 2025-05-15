/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:10:34 by dfeve             #+#    #+#             */
/*   Updated: 2024/11/11 12:59:43 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		size;
	char	*result;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		result = malloc(1);
		if (!result)
			return (NULL);
		result[0] = '\0';
	}
	else
	{
		if (start + len > ft_strlen(s))
			size = ft_strlen(s) - start + 1;
		else
			size = len + 1;
		result = malloc(size);
		ft_strlcpy(result, s + start, size);
	}
	return (result);
}
