/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:13:08 by quentin8340       #+#    #+#             */
/*   Updated: 2025/06/03 13:20:02 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_unset(char ***envp, char *name)
{
	int	i;
	int	len;
	char *trimmed;
	
	i = 0;
	while (i++ < 5)
		name++;
	trimmed = ft_strtrim(name, " \f\t\n\r\v");
	i = 0;
	if (!envp || !*envp || !trimmed)
		return (1);
	len = strlen(trimmed);
	while ((*envp)[i])
	{
		if (strncmp((*envp)[i], trimmed, len) == 0 && (*envp)[i][len] == '=')
		{
			free((*envp)[i]);
			while ((*envp)[i + 1])
			{
				(*envp)[i] = (*envp)[i + 1];
				i++;
			}
			(*envp)[i] = NULL;
			break ;
		}
		else
			i++;
	}
	free(trimmed);
	return (0);
}
