/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:27:14 by gdalmass          #+#    #+#             */
/*   Updated: 2024/11/11 15:56:33 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

// void    main()
// {
//     printf("A: %d \n", ft_isalpha('A'));
//     printf("F: %d \n", ft_isalpha('F'));
//     printf("Z: %d \n", ft_isalpha('Z'));
//     printf("a: %d \n", ft_isalpha('a'));
//     printf("f: %d \n", ft_isalpha('f'));
//     printf("z: %d \n", ft_isalpha('z'));
//     printf("_: %d \n", ft_isalpha('_'));
//     printf("=: %d \n", ft_isalpha('='));
//     printf("1: %d \n", ft_isalpha('1'));
// }