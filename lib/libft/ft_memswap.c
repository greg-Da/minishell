/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:53:58 by greg              #+#    #+#             */
/*   Updated: 2025/06/18 11:30:52 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memswap(void *p1, void *p2, size_t size)
{
	void	*tmp;

	tmp = malloc(size);
	if (!tmp)
		return (-1);
	ft_memcpy(tmp, p1, size);
	ft_memcpy(p1, p2, size);
	ft_memcpy(p2, tmp, size);
	free(tmp);
	return (0);
}
