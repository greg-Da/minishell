/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:13:08 by quentin8340       #+#    #+#             */
/*   Updated: 2025/06/05 17:13:57 by qbaret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_unset(t_minish *manager, char *arg)
{
	char	**args;
	char	*key;
	char	**new_env;
	int		i, j, k, len, skip;
	int		status = 0;

	if (ft_strncmp(arg, "unset", 5) == 0)
	{
		arg += 5;
		while (*arg == ' ' || *arg == '\t')
			arg++;
	}

	args = ft_split(arg, ' ');
	if (!args)
		return (1);

	for (k = 0; args[k]; k++)
	{
		key = remove_double_quotes(args[k]);
		if (!key)
		{
			status = 1;
			continue;
		}
		len = ft_strlen(key);
		i = 0;
		j = 0;
		while (manager->envp[i])
			i++;
		new_env = ft_calloc(i + 1, sizeof(char *));
		if (!new_env)
		{
			free(key);
			status = 1;
			continue;
		}
		i = 0;
		while (manager->envp[i])
		{
			skip = (ft_strncmp(manager->envp[i], key, len) == 0 &&
					(manager->envp[i][len] == '=' || manager->envp[i][len] == '\0'));
			if (skip)
				free(manager->envp[i]);
			else
				new_env[j++] = manager->envp[i];
			i++;
		}
		new_env[j] = NULL;
		free(manager->envp);
		manager->envp = new_env;
		free(key);
	}
	free_split(args);
	return (status);
}


