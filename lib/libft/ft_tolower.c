/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:41:24 by gdalmass          #+#    #+#             */
/*   Updated: 2024/11/11 16:21:49 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if ((c >= 'A' && c <= 'Z'))
		return (c + 32);
	return (c);
}

// void main()
// {
//     printf("t=%c \n", ft_tolower('t'));
//     printf("A=%c \n", ft_tolower('A'));
//     printf("5=%c \n", ft_tolower('5'));
// }