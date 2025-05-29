/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:13:08 by quentin8340       #+#    #+#             */
/*   Updated: 2025/05/29 18:45:46 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_unset(char ***envp, char *arg)
{
	int i = 1;
	int j, k;
	char *name;

	while (*envp[i])
	{
		name = arg;
		j = 0;
		while (*envp[j])
		{
			if (ft_strncmp(*envp[j], name, ft_strlen(name)) == 0 &&
				*envp[j][ft_strlen(name)] == '=')
			{
				free(*envp[j]);
				k = j;
				while (*envp[k])
				{
					
                    *envp[k] = *envp[k + 1];
					k++;
				}
			}
			else
				j++;
		}
		i++;
	}
}

