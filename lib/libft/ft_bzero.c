/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:07:39 by dfeve             #+#    #+#             */
/*   Updated: 2024/11/11 14:14:49 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = '\0';
		i++;
	}
}
/*
int main()
{
    // Test case 1: Normal case with non-zero length
    char buffer[10] = "abcdefghi";
    ft_bzero(buffer, 5);  // Zero out the first 5 characters
    
    // Check that the first 5 characters are zeroed
    for (size_t i = 0; i < 5; i++) {
        assert(buffer[i] == '\0');  // These should be zero
    }
    // Check that the remaining characters are untouched
    assert(buffer[5] == 'f');
    assert(buffer[6] == 'g');
    assert(buffer[7] == 'h');
    assert(buffer[8] == 'i');
    assert(buffer[9] == '\0');  // Null terminator from the original string

    // Test case 2: Edge case with zero length
    char buffer2[10] = "123456789";
    ft_bzero(buffer2, 0);  // Should not modify any bytes
    assert(strcmp(buffer2, "123456789") == 0);
    // Test case 3: Edge case where n is larger than the buffer length
    char buffer3[10] = "abcdefghi";
    ft_bzero(buffer3, 10);  // Zero out the entire buffer
    for (size_t i = 0; i < 10; i++) {
        assert(buffer3[i] == '\0');  // All characters should be zero
    }

    printf("All tests passed successfully.\n");
}*/
