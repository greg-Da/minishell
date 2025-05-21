/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:12:12 by gdalmass          #+#    #+#             */
/*   Updated: 2024/11/11 15:58:17 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_ten_pow(int n)
{
	int	i;

	i = 1;
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*ft_pop_str(char *dest, int nmb, int index)
{
	dest[index] = 0;
	index--;
	while (nmb > 9)
	{
		dest[index] = '0' + (nmb % 10);
		nmb /= 10;
		index--;
	}
	dest[index] = '0' + nmb;
	return (dest);
}

char	*ft_itoa(int n)
{
	int		pos;
	int		len;
	char	*str;

	pos = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		pos = 1;
		n *= -1;
	}
	len = ft_get_ten_pow(n);
	str = malloc((len + pos + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (pos)
		str[0] = '-';
	return (ft_pop_str(str, n, len + pos));
}

// int main(void)
// {
//     char *str = ft_itoa(-21);
//     printf("%s", str);
//     free(str);
// }