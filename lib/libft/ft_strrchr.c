/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:25:56 by gdalmass          #+#    #+#             */
/*   Updated: 2024/11/11 16:19:46 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *str, int chr)
{
	int				i;
	int				last;
	int				occurence;
	unsigned char	c;

	i = 0;
	occurence = 0;
	c = (unsigned char)chr;
	while (str[i])
	{
		if (str[i] == c)
		{
			occurence = 1;
			last = i;
		}
		i++;
	}
	if (str[i] == c)
		return (&str[i]);
	if (occurence)
		return (&str[last]);
	return (NULL);
}

// void main()
// {
//     printf("%s", ft_strrchr("hello", 'e'));
// }