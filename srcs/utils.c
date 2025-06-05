/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:46:30 by greg              #+#    #+#             */
/*   Updated: 2025/06/05 15:30:58 by qbaret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_res_size(char *str)
{
	int		i;
	int		len;
	char	quote_type;
	char	*result;

	i = 0;
	len = 0;
	quote_type = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (!quote_type && (str[i] == '\'' || str[i] == '"'))
			quote_type = str[i];
		else if (quote_type && str[i] == quote_type)
			quote_type = 0;
		else
			len++;
		i++;
	}
	result = malloc(len + 1);
	return (result);
}

void	free_pipes(char **pipes)
{
	int	i;

	i = 0;
	if (!pipes)
		return ;
	while (pipes[i])
		free(pipes[i++]);
	free(pipes);
}
char *ft_strjoin_three(char *s1, char *s2, char *s3)
{
	char	*res;
	size_t	len1 = ft_strlen(s1);
	size_t	len2 = ft_strlen(s2);
	size_t	len3 = ft_strlen(s3);

	res = malloc(len1 + len2 + len3 + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, len1 + 1);
	ft_strlcat(res, s2, len1 + len2 + 1);
	ft_strlcat(res, s3, len1 + len2 + len3 + 1);
	return (res);
}
char **append_str_to_array(char **env, char *str)
{
	int		len = 0;
	char	**new_env;

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
	new_var = ft_strjoin_three(key, "=", value); // crée "KEY=VALUE"
	if (!new_var)
		return (1);

	// Cherche si la variable existe déjà
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

	// Ajoute une nouvelle variable
	manager->envp = append_str_to_array(manager->envp, new_var);
	free(new_var);
	return (0);
}


