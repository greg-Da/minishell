/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:26:10 by greg              #+#    #+#             */
/*   Updated: 2024/11/11 16:20:22 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_include(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

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