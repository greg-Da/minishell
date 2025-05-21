/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:29:01 by gdalmass          #+#    #+#             */
/*   Updated: 2024/11/11 16:06:10 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *pnt, int val, int count)
{
	int		i;
	char	*mem;

	i = 0;
	mem = (char *)pnt;
	while (i < count)
	{
		mem[i] = val;
		i++;
	}
	return ((void *)mem);
}

// void    main()
// {
//     char * a = calloc(10, sizeof(char));
//     char * b = calloc(10, sizeof(char));
//     ft_memset(a, 2000, 5);
//     memset(b, 2000, 5);
//     int i = 0;
//     while(i < 8)
//     {
//         printf("%d", a[i]);
//         i++;
//     }
//     i = 0;
//     printf("\n");
//     while(i < 8)
//     {
//         printf("%d", b[i]);
//         i++;
//     }
//     free(a);
//     free(b);
// }