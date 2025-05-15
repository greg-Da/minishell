/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:44:55 by dfeve             #+#    #+#             */
/*   Updated: 2024/11/11 14:23:34 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		size;
	char	*result;

	i = 0;
	size = (int)ft_strlen(s);
	result = malloc((size * sizeof(char)) + 1);
	if (!result)
		return (NULL);
	while (i < size)
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*
int main()
{
	char *test = "Bien jouer, tu sais allouer!";
	char *f1 = ft_strdup(test);
	char *f2 = strdup(test);
	printf("my func: %s\nreal func: %s\n", f1, f2);
}*/
