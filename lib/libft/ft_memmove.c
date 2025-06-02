/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:29:49 by gdalmass          #+#    #+#             */
/*   Updated: 2024/11/12 13:09:58 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, void *src, int size)
{
	int		i;
	char	*ndest;
	char	*nsrc;

	if (!dest && !src)
		return (NULL);
	i = -1;
	ndest = (char *)dest;
	nsrc = (char *)src;
	if (ndest > nsrc && ndest < nsrc + size)
	{
		while (size > ++i)
			ndest[(size - 1) - i] = nsrc[(size - 1) - i];
	}
	else
	{
		while (size > ++i)
			ndest[i] = nsrc[i];
	}
	return ((void *)dest);
}
