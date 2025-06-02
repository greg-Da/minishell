/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:49:21 by gdalmass          #+#    #+#             */
/*   Updated: 2025/05/21 14:52:02 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*str;
	int		i;
	int		length;

	i = 0;
	length = ft_strlen(src) + 1;
	str = malloc (length * sizeof(char));
	if (!str)
		return (NULL);
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

// int	main(void)
// {
// 	char	*t;
// 	char	d[] = "abc";
// 	t = ft_strdup(d);
// 	printf("%s", t);
// 	free(t);
// }
