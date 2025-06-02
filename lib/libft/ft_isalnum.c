/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:27:14 by gdalmass          #+#    #+#             */
/*   Updated: 2024/11/11 15:56:37 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

// void    main()
// {
//     printf("A: %d \n", ft_isalnum('A'));
//     printf("F: %d \n", ft_isalnum('F'));
//     printf("Z: %d \n", ft_isalnum('Z'));
//     printf("a: %d \n", ft_isalnum('a'));
//     printf("f: %d \n", ft_isalnum('f'));
//     printf("z: %d \n", ft_isalnum('z'));
//     printf("_: %d \n", ft_isalnum('_'));
//     printf("=: %d \n", ft_isalnum('='));
//     printf("1: %d \n", ft_isalnum('1'));
// }