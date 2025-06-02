/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:49:45 by gdalmass          #+#    #+#             */
/*   Updated: 2024/11/11 15:56:41 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(int count, size_t size)
{
	void	*mem;

	if (count != 0 && size > SIZE_MAX / count)
		return (NULL);
	mem = malloc(count * size);
	if (!mem)
	{
		return (NULL);
	}
	ft_bzero(mem, size * count);
	return ((void *)mem);
}

// void	main()
// {
//     int *a = ft_calloc(10, sizeof(int));
//     int i = 0;
//     while (i < 10)
//     {
//         printf("%d", a[i]);
//         i++;
//     }
//     free(a);
// }