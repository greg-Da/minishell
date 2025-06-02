/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:47:39 by gdalmass          #+#    #+#             */
/*   Updated: 2024/11/12 13:17:44 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcat(char *dest, char *src, unsigned int nb)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	len_dest;
	unsigned int	len_src;

	len_dest = 0;
	while (dest && dest[len_dest])
		len_dest++;
	len_src = 0;
	while (src[len_src])
		len_src++;
	if (nb == 0)
		return (len_src);
	if (nb <= len_dest)
		return (nb + len_src);
	i = len_dest;
	j = 0;
	while (src[j] && i < nb - 1)
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (len_dest + len_src);
}

// int main() {
//     char *d = calloc(10, 1);
//     char s[] = "Salut";
//     strcpy(d, "Bonjour");
//     printf("%ld \n", strlcat(d, "Salut", 10));
//     printf("%s", d);
//     return 0;
// }