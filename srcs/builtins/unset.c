/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:13:08 by quentin8340       #+#    #+#             */
/*   Updated: 2025/06/04 10:54:56 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_unset(t_minish *manager, char *name)
{
	int	i;
	int	len;
	char *trimmed;
	
	i = 0;
	while (i++ < 5)
		name++;
	trimmed = ft_strtrim(name, " \f\t\n\r\v");
	i = 0;
	if (!manager->envp || !*manager->envp || !trimmed)
		return (1);
	len = strlen(trimmed);
	while ((manager->envp)[i]) 
	{
		if (strncmp((manager->envp)[i], trimmed, len) == 0 && (manager->envp)[i][len] == '=')
		{
			free((manager->envp)[i]);
			while ((manager->envp)[i + 1])
			{
				(manager->envp)[i] = (manager->envp)[i + 1];
				i++;
			}
			(manager->envp)[i] = NULL;
			break ;
		}
		else
			i++;
	}
	free(trimmed);
	return (0);
}
