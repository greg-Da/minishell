/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_and_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:44:10 by quentin8340       #+#    #+#             */
/*   Updated: 2025/06/16 11:53:47 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*remove_space_before_redir(char *str)
{
	int		i;
	int		j;
	int		k;
	char	*res;

	i = 0;
	j = 0;
	k = 0;
	res = malloc(strlen(str) + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (is_between_any_quotes(str, i))
		{
			while (str[i] && is_between_any_quotes(str, i))
				res[j++] = str[i++];
			continue ;
		}
		if (ft_include(str[i], " \t\n\r\v"))
		{
			k = i;
			while (ft_include(str[k], " \t\n\r\v"))
				k++;
			if ((str[k] == '<' || str[k] == '>') && !is_between_any_quotes(str,
					k))
			{
				i = k;
				continue ;
			}
		}
		res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}

char	**append_str_to_array(char **env, char *str)
{
	int		len;
	char	**new_env;

	len = 0;
	while (env && env[len])
		len++;
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (NULL);
	for (int i = 0; i < len; i++)
		new_env[i] = ft_strdup(env[i]);
	new_env[len] = ft_strdup(str);
	new_env[len + 1] = NULL;
	free_split(env);
	return (new_env);
}

int	set_env_key_value(t_minish *manager, char *key, char *value)
{
	int		i;
	char	*new_var;
	size_t	key_len;

	if (!manager || !key || !value)
		return (1);
	key_len = ft_strlen(key);
	new_var = ft_strjoin_three(key, "=", value);
	if (!new_var)
		return (1);
	for (i = 0; manager->envp[i]; i++)
	{
		if (ft_strncmp(manager->envp[i], key, key_len) == 0
			&& manager->envp[i][key_len] == '=')
		{
			free(manager->envp[i]);
			manager->envp[i] = new_var;
			return (0);
		}
	}
	manager->envp = append_str_to_array(manager->envp, new_var);
	free(new_var);
	return (0);
}
