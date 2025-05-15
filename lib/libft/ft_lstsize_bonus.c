/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:15:43 by dfeve             #+#    #+#             */
/*   Updated: 2024/11/12 17:26:46 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
/*
int main()
{
	t_list	*test;
	test = ft_lstnew("caca");
	t_list	*next;
	next = ft_lstnew("popo");
	test->next = next;
	printf("%d\n", ft_lstsize(test));
}*/
