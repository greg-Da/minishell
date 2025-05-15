/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:28:33 by dfeve             #+#    #+#             */
/*   Updated: 2024/11/11 14:23:56 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	check_len1(char const *s1)
{
	if (!s1)
		return (0);
	return (ft_strlen(s1));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		i;
	size_t	len_s1;
	size_t	len_s2;
	size_t	result_len;

	len_s1 = check_len1(s1);
	len_s2 = check_len1(s2);
	result_len = len_s1 + len_s2 + 1;
	result = malloc(result_len);
	i = 0;
	if (!result)
		return (NULL);
	while (i < (int)result_len - 1)
	{
		if (i < (int)len_s1 && s1[i])
			result[i] = s1[i];
		else
			result[i] = s2[i - (int)len_s1];
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*
int main()
{
	char *hello = ft_strjoin(NULL, "halo");
	printf("%s\n", hello);
}*/
