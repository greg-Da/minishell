/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:20:15 by dfeve             #+#    #+#             */
/*   Updated: 2024/11/11 17:15:36 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*s;

	if (!*lst || !lst)
	{
		*lst = new;
		return ;
	}
	s = *lst;
	while (s->next)
		s = s->next;
	s->next = new;
}
