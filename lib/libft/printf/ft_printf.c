/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:21:26 by dfeve             #+#    #+#             */
/*   Updated: 2024/12/02 05:38:30 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	fonction(va_list args)
{
	int					count;
	unsigned long long	f;

	count = 0;
	f = va_arg(args, unsigned long long);
	if (f == 0)
		count += ft_putstr_fdd("(nil)", 1);
	else
	{
		count += ft_putstr_fdd("0x", 1);
		count += ft_pitohex(f, 0);
	}
	return (count);
}

static int	manage_percent(const char *str, int *i, va_list args)
{
	int	count;

	count = 0;
	if (str[*i + 1] == 'd' || str[*i + 1] == 'i')
		count += ft_putnbr_fdd(va_arg(args, int), 1);
	else if (str[*i + 1] == 'c')
		count += ft_putchar_fdd(va_arg(args, int), 1);
	else if (str[*i + 1] == 's')
		count += ft_putstr_fdd(va_arg(args, char *), 1);
	else if (str[*i + 1] == '%')
		count += ft_putchar_fdd('%', 1);
	else if (str[*i + 1] == 'x' || str[*i + 1] == 'X')
		count += ft_itohex(va_arg(args, unsigned int), str[*i + 1] != 'x');
	else if (str[*i + 1] == 'u')
		count += ft_uputnbr_fd(va_arg(args, unsigned int), 1);
	else if (str[*i + 1] == 'p')
		count += fonction(args);
	*i = *i + 2;
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
			count += manage_percent(str, &i, args);
		else
		{
			ft_putchar_fdd(str[i], 1);
			count++;
			i++;
		}
	}
	va_end(args);
	return (count);
}
