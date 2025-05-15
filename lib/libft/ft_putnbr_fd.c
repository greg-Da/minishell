/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:39:38 by dfeve             #+#    #+#             */
/*   Updated: 2024/11/11 14:22:40 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	recursive_putnbr(int n, int fd)
{
	if (n < 10)
	{
		ft_putchar_fd(n + '0', fd);
		return ;
	}
	recursive_putnbr(n / 10, fd);
	ft_putchar_fd((n % 10) + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	num;

	num = n;
	if (n == INT_MIN)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		num = -num;
	}
	recursive_putnbr(num, fd);
}
