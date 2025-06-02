/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:27:14 by gdalmass          #+#    #+#             */
/*   Updated: 2024/11/11 15:56:17 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

// void    main()
// {
//     printf("A: %d \n", ft_isprint('A'));
//     printf("F: %d \n", ft_isprint('F'));
//     printf("Z: %d \n", ft_isprint('Z'));
//     printf("a: %d \n", ft_isprint('a'));
//     printf("f: %d \n", ft_isprint('f'));
//     printf("z: %d \n", ft_isprint('z'));
//     printf("_: %d \n", ft_isprint('_'));
//     printf("=: %d \n", ft_isprint('='));
//     printf("1: %d \n", ft_isprint('1'));
//     printf("?: %d \n", ft_isprint(130));
//     printf("?: %d \n", ft_isprint(2));
// }