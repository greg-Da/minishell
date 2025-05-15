/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:23:27 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/10 19:50:48 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	calc_size(int n)
{
	int	num;
	int	result;

	num = n;
	result = 0;
	if (n < 0)
	{
		num = -num;
		result++;
	}
	while (num > 9)
	{
		num = num / 10;
		result++;
	}
	result++;
	return (result);
}

static int	check(int n)
{
	if (n != INT_MIN)
		return (0);
	return (1);
}

static char	*return_error(void)
{
	char	*result;

	result = malloc(12);
	if (!result)
		return (NULL);
	ft_strlcpy(result, "-2147483648", 12);
	return (result);
}

char	*ft_itoa(int n)
{
	int		num;
	int		i;
	int		size;
	char	*result;

	if (check(n) == 1)
		return (return_error());
	num = n;
	i = 0;
	size = calc_size(n);
	result = malloc(size + 1);
	if (!result)
		return (NULL);
	if (n < 0)
		result[0] = '-';
	num = ft_abs(num);
	while (num > 9)
	{
		result[(size - 1) - i] = (char)(num % 10) + '0';
		num = num / 10;
		i++;
	}
	result[(size - 1) - i] = (char)(num % 10) + '0';
	result[size] = '\0';
	return (result);
}
/*
int main()
{
	printf("%s\n", ft_itoa(-0));
}*/
