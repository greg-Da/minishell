/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:27:14 by gdalmass          #+#    #+#             */
/*   Updated: 2024/11/11 15:56:26 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}

// void    main()
// {
//     printf("A: %d \n", ft_isdigit('A'));
//     printf("F: %d \n", ft_isdigit('F'));
//     printf("Z: %d \n", ft_isdigit('Z'));
//     printf("a: %d \n", ft_isdigit('a'));
//     printf("f: %d \n", ft_isdigit('f'));
//     printf("z: %d \n", ft_isdigit('z'));
//     printf("_: %d \n", ft_isdigit('_'));
//     printf("=: %d \n", ft_isdigit('='));
//     printf("1: %d \n", ft_isdigit('1'));
//     printf("5: %d \n", ft_isdigit('5'));
//     printf("0: %d \n", ft_isdigit('0'));
//     printf("9: %d \n", ft_isdigit('9'));
// }