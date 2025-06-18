/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:13:08 by quentin8340       #+#    #+#             */
/*   Updated: 2025/06/18 13:26:30 by qbaret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*skip_unset_prefix(char *arg)
{
	if (ft_strncmp(arg, "unset", 5) == 0)
	{
		arg += 5;
		while (*arg == ' ' || *arg == '\t')
			arg++;
	}
	return (arg);
}

static int	count_env_vars(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

static char	**build_new_env(char **envp, char *key, int skip)
{
	int		i;
	int		j;
	int		len;
	char	**new_env;
	int		env_count;

	i = 0;
	j = 0;
	len = ft_strlen(key);
	env_count = count_env_vars(envp);
	new_env = ft_calloc(env_count + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	while (envp[i])
	{
		skip = (ft_strncmp(envp[i], key, len) == 0 && (envp[i][len] == '='
					|| envp[i][len] == '\0'));
		if (skip)
			free(envp[i]);
		else
			new_env[j++] = envp[i];
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

static int	unset_key(t_minish *manager, char *arg)
{
	char	*key;
	char	**new_env;

	key = strip_quotes(arg);
	if (!key)
		return (1);
	new_env = build_new_env(manager->envp, key, 0);
	free(key);
	if (!new_env)
		return (1);
	free(manager->envp);
	manager->envp = new_env;
	return (0);
}

int	ft_unset(t_minish *manager, char *arg)
{
	char	**args;
	int		status;
	int		k;

	status = 0;
	k = 0;
	arg = skip_unset_prefix(arg);
	args = split_args_preserving_quotes(arg);
	if (!args)
		return (1);
	while (args[k])
	{
		if (unset_key(manager, args[k]))
			status = 1;
		k++;
	}
	free_split(args);
	return (status);
}
