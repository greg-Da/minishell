/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:14:41 by gdalmass          #+#    #+#             */
/*   Updated: 2024/11/12 13:12:57 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *str, char *to_find, int len)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	if ((!str || !to_find) && len == 0)
		return (NULL);
	if (!to_find[i])
		return (str);
	while (str[i])
	{
		j = 0;
		if (str[i] == to_find[j])
		{
			start = i;
			while (str[i] == to_find[j] && (len > i || len == -1))
			{
				i++;
				if (to_find[++j] == '\0')
					return (&str[start]);
			}
		}
		i = i - j + 1;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char haystack[30] = "aaabcabcd";
// 	char needle[10] = "aabc";
// 	printf("ft V :%s \n", ft_strnstr(haystack, needle, -1));
// 	printf("ft V :%s \n", strnstr(haystack, needle, -1));
// 	printf("ft V :%s \n", ft_strnstr(haystack, "abcd", 9));
// 	printf("ft V :%s \n", ft_strnstr(haystack, "abcd", 9));
// }