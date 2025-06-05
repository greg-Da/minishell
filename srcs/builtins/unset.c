/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:13:08 by quentin8340       #+#    #+#             */
/*   Updated: 2025/06/05 13:41:39 by qbaret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_unset(t_minish *manager, char *arg)
{
	char	*key;
	char	**new_env;
	int		i, j;
	int		len;

	while (*arg && (*arg == ' ' || *arg == '\t'))
		arg++;
	arg += 5;
	while (*arg == ' ')
		arg++;

	key = remove_double_quotes(arg);
	if (!key)
		return (1);

	len = ft_strlen(key);
	i = 0;
	j = 0;

	while (manager->envp[i])
		i++;
	new_env = ft_calloc(i + 1, sizeof(char *));
	if (!new_env)
		return (free(key), 1);

	i = 0;
	while (manager->envp[i])
	{
		if (ft_strncmp(manager->envp[i], key, len) == 0 &&
			(manager->envp[i][len] == '=' || manager->envp[i][len] == '\0'))
		{
			free(manager->envp[i]);
		}
		else
		{
			new_env[j++] = manager->envp[i];
		}
		i++;
	}
	new_env[j] = NULL;
	free(manager->envp);
	manager->envp = new_env;
	free(key);
	return (0);
}

