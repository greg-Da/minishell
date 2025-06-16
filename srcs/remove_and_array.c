/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_and_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:44:10 by quentin8340       #+#    #+#             */
/*   Updated: 2025/06/16 13:38:21 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int skip_spaces(char *str, int *i)
{
    int k;

	k = *i;

    if (ft_include(str[k], " \t\n\r\v"))
    {
        while (ft_include(str[k], " \t\n\r\v"))
            k++;
        if ((str[k] == '<' || str[k] == '>') && !is_between_any_quotes(str, k))
        {
            *i = k;
            return (0);
        }
    }
    return (1);
}

char *remove_space_before_redir(char *str)
{
    int i = 0;
    int j = 0;
    char *res = malloc(strlen(str) + 1);
    
    if (!res)
        return (NULL);
        
    while (str[i])
    {
        if (is_between_any_quotes(str, i))
        {
            while (str[i] && is_between_any_quotes(str, i))
                res[j++] = str[i++];
            continue;
        }
        if (skip_spaces(str, &i) == 0)
            continue;
        res[j++] = str[i++];
    }
    res[j] = '\0';
    return (res);
}

char **append_str_to_array(char **env, char *str)
{
	int len;
	char **new_env;

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

int set_env_key_value(t_minish *manager, char *key, char *value)
{
	int i;
	char *new_var;
	size_t key_len;

	if (!manager || !key || !value)
		return (1);
	key_len = ft_strlen(key);
	new_var = ft_strjoin_three(key, "=", value);
	if (!new_var)
		return (1);
	for (i = 0; manager->envp[i]; i++)
	{
		if (ft_strncmp(manager->envp[i], key, key_len) == 0 && manager->envp[i][key_len] == '=')
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
