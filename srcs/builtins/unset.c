/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:13:08 by quentin8340       #+#    #+#             */
/*   Updated: 2025/05/30 09:25:55 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_unset(char ***envp, char *name)
{
	int i = 0;
	int len;

	if (!envp || !*envp || !name)
		return;

	len = strlen(name);
	while ((*envp)[i])
	{
		if (strncmp((*envp)[i], name, len) == 0 && (*envp)[i][len] == '=')
		{
			free((*envp)[i]);
			while ((*envp)[i + 1])
			{
				(*envp)[i] = (*envp)[i + 1];
				i++;
			}
			(*envp)[i] = NULL;
			break;
		}
		else
			i++;
	}
}

