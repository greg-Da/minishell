/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:26:10 by greg              #+#    #+#             */
/*   Updated: 2025/06/05 13:03:36 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen((char *)s1) - 1;
	while (ft_include(s1[i], set))
		i++;
	while (ft_include(s1[len], set))
		len--;
	return (ft_substr(s1, (unsigned int)i, (size_t)(len - i + 1)));
}

// int main(void)
// {
//     printf("%s", ft_strtrim("tripouille   xxx", " x"));
// }