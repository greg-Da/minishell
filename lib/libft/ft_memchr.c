/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:23:20 by gdalmass          #+#    #+#             */
/*   Updated: 2024/11/11 16:03:07 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void *pnt, int chr, int size)
{
	int				i;
	unsigned char	*str;
	unsigned char	c;

	i = 0;
	str = (unsigned char *)pnt;
	c = (unsigned char)chr;
	while (i < size)
	{
		if (str[i] == c)
			return ((void *)&str[i]);
		i++;
	}
	return (NULL);
}

// int main() {
//     char s[] = {0, 1, 2 ,3 ,4 ,5};
// 	printf("FT : %p \n", ft_memchr(s, 2 + 256, 3));
//     printf("OG : %p", memchr(s, 2 + 256, 3));
//     return 0;
// }