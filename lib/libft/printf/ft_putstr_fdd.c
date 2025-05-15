/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:31:50 by dfeve             #+#    #+#             */
/*   Updated: 2024/11/24 02:01:54 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putstr_fdd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return (ft_putstr_fdd("(null)", 1));
	while (s[i])
	{
		ft_putchar_fdd(s[i], fd);
		i++;
	}
	return (i);
}
