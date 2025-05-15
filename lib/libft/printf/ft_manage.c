/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:51:38 by dfeve             #+#    #+#             */
/*   Updated: 2024/11/24 02:05:49 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	print_nb(unsigned int i, int maj)
{
	if (i < 10)
	{
		ft_putnbr_fdd(i, 1);
	}
	else if (i < 16)
	{
		if (maj == 1)
			ft_putchar_fdd((i - 10) + 'A', 1);
		else
			ft_putchar_fdd((i - 10) + 'a', 1);
	}
	return (1);
}

int	ft_itohex(unsigned int i, int maj)
{
	int	count;

	count = 0;
	if (i < 16)
	{
		count += print_nb(i, maj);
		return (1);
	}
	count += ft_itohex(i / 16, maj);
	count += print_nb(i % 16, maj);
	return (count);
}

static char	pprint_nb(unsigned long long i, int maj)
{
	if (i < 10)
		ft_putnbr_fdd(i, 1);
	else if (i < 16)
	{
		if (maj == 1)
			ft_putchar_fdd((i - 10) + 'A', 1);
		else
			ft_putchar_fdd((i - 10) + 'a', 1);
	}
	return (1);
}

int	ft_pitohex(unsigned long long i, int maj)
{
	int	count;

	count = 0;
	if (i < 16)
	{
		count += pprint_nb(i, maj);
		return (count);
	}
	count += ft_pitohex(i / 16, maj);
	count += pprint_nb(i % 16, maj);
	return (count);
}
