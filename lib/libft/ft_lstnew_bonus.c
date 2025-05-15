/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:40:48 by dfeve             #+#    #+#             */
/*   Updated: 2024/11/12 23:24:08 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*result;

	if (!content)
		return (NULL);
	result = malloc(sizeof(t_list));
	result->content = content;
	result->next = NULL;
	return (result);
}
/*
int main()
{
	t_list	*test;
	test = ft_lstnew("hey");
	printf("%s\n", (char *)test->content);
}*/
