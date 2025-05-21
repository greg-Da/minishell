/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:03:55 by gdalmass          #+#    #+#             */
/*   Updated: 2024/11/19 13:04:44 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *src, size_t n)
{
	char	*str;
	size_t		i;
	size_t		length;

	i = 0;
	if (!src)
		return (NULL);
	length = (size_t)ft_strlen(src);
	if (n < length)
		length = n;
	str = malloc ((length + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < length)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
