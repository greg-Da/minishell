/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:39:38 by dfeve             #+#    #+#             */
/*   Updated: 2024/11/24 02:06:35 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	recursive_putnbr(int n, int fd)
{
	int	count;

	count = 0;
	count++;
	if (n < 10)
	{
		ft_putchar_fdd(n + '0', fd);
		return (1);
	}
	count += recursive_putnbr(n / 10, fd);
	ft_putchar_fdd((n % 10) + '0', fd);
	return (count);
}

int	ft_putnbr_fdd(int n, int fd)
{
	int	num;
	int	count;

	num = n;
	count = 0;
	if (n == INT_MIN)
	{
		ft_putstr_fdd("-2147483648", fd);
		return (11);
	}
	if (n < 0)
	{
		ft_putchar_fdd('-', fd);
		num = -num;
		count++;
	}
	count += recursive_putnbr(num, fd);
	return (count);
}

static int	urecursive_putnbr(unsigned int n, int fd)
{
	int	count;

	count = 0;
	count++;
	if (n < 10)
	{
		ft_putchar_fdd(n + '0', fd);
		return (1);
	}
	count += urecursive_putnbr(n / 10, fd);
	ft_putchar_fdd((n % 10) + '0', fd);
	return (count);
}

int	ft_uputnbr_fd(unsigned int n, int fd)
{
	int	num;
	int	count;

	num = n;
	count = 0;
	count += urecursive_putnbr(num, fd);
	return (count);
}
