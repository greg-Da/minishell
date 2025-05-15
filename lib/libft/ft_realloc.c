/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:33:47 by greg              #+#    #+#             */
/*   Updated: 2025/02/10 18:08:19 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_size));
	new = malloc(new_size);
	if (new == NULL)
		return (NULL);
	if (new_size > old_size)
		ft_memcpy(new, ptr, old_size);
	else
		ft_memcpy(new, ptr, new_size);
	free(ptr);
	return (new);
}