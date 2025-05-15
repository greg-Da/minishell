/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 22:50:02 by dfeve             #+#    #+#             */
/*   Updated: 2024/11/11 17:20:19 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*l;

	if (!f || !del)
		return (NULL);
	result = NULL;
	while (lst)
	{
		l = ft_lstnew((*f)(lst->content));
		if (!l)
		{
			while (result)
			{
				l = result->next;
				(*del)(result->content);
				free(result);
				result = l;
			}
			lst = NULL;
			return (NULL);
		}
		ft_lstadd_back(&result, l);
		lst = lst->next;
	}
	return (result);
}
