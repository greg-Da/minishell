/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:27:14 by gdalmass          #+#    #+#             */
/*   Updated: 2024/11/11 15:56:30 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

// void    main()
// {
//     printf("A: %d \n", ft_isascii('A'));
//     printf("F: %d \n", ft_isascii('F'));
//     printf("Z: %d \n", ft_isascii('Z'));
//     printf("a: %d \n", ft_isascii('a'));
//     printf("f: %d \n", ft_isascii('f'));
//     printf("z: %d \n", ft_isascii('z'));
//     printf("_: %d \n", ft_isascii('_'));
//     printf("=: %d \n", ft_isascii('='));
//     printf("1: %d \n", ft_isascii('1'));
//     printf("?: %d \n", ft_isascii(130));
// }