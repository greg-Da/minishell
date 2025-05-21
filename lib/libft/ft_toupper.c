/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:41:24 by gdalmass          #+#    #+#             */
/*   Updated: 2024/11/11 16:22:02 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if ((c >= 'a' && c <= 'z'))
		return (c - 32);
	return (c);
}

// void main()
// {
//     printf("t=%c \n", ft_toupper('t'));
//     printf("A=%c \n", ft_toupper('A'));
//     printf("5=%c \n", ft_toupper('5'));
// }