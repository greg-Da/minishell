/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:25:34 by gdalmass          #+#    #+#             */
/*   Updated: 2024/11/12 11:32:32 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, int size)
{
	int			i;
	char		*ndest;
	const char	*nsrc;

	if (!dest && !src)
		return (NULL);
	i = 0;
	ndest = (char *)dest;
	nsrc = (const char *)src;
	while (i < size)
	{
		ndest[i] = nsrc[i];
		i++;
	}
	return ((void *)dest);
}

// void    main()
// {
//     char * a = calloc(10, sizeof(char));
//     char * b = calloc(10, sizeof(char));
//     memset(a, 1, 6);
//     memset(a, 2, 4);
//     ft_memcpy(b, a, 7);
//     int i = 0;
//     while(i < 10)
//     {
//         printf("%d", b[i]);
//         i++;
//     }
//     free(a);
//     free(b);
// }