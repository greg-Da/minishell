/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:29:01 by gdalmass          #+#    #+#             */
/*   Updated: 2024/11/11 15:51:36 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *pnt, size_t count)
{
	size_t	i;
	char	*mem;

	i = 0;
	mem = (char *)pnt;
	while (i < count)
	{
		mem[i] = 0;
		i++;
	}
	return ((void *)mem);
}
