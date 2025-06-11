/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:46:30 by greg              #+#    #+#             */
/*   Updated: 2025/06/11 17:38:47 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_between_any_quotes(char *str, int i)
{
	return (is_between_char(str, i, '\'') || is_between_char(str, i, '"'));
}

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
char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	char	*res;
	size_t	len1;
	size_t	len2;
	size_t	len3;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	res = malloc(len1 + len2 + len3 + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, len1 + 1);
	ft_strlcat(res, s2, len1 + len2 + 1);
	ft_strlcat(res, s3, len1 + len2 + len3 + 1);
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

char	*remove_space_before_redir(char *str)
{
	int		i = 0, j = 0, k;
	char	*res;

	i = 0, j = 0, k = 0;
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

int	skip_quotes(char *input, int i)
{
	if (is_between_any_quotes(input, ++i))
	{
		while (input[i] && input[i] != '\'' && input[i] != '"')
			i++;
	}
	i++;
	if (input[i] == '\'' || input[i] == '"')
		return (skip_quotes(input, i));
	return (i);
}

char	*skip_redir_and_filename(char *str)
{
	int i = 0, j = 0;
	char *res = malloc(strlen(str) + 1);
	char *input;

	if (!res)
		return (NULL);

	input = remove_space_before_redir(str);
	free(str);

	while (input[i])
	{
		if (((input[i] == '>' || input[i] == '<')
				&& !is_between_any_quotes(input, i)))
		{
			i++;
			if (input[i] == input[i - 1])
				i++;

			while (input[i] && ft_include(input[i], " \t\n\r\v"))
				i++;

			if (input[i] == '\'' || input[i] == '"')
				i = skip_quotes(input, i);
			else
			{
				while (input[i] && !ft_include(input[i], " \t\n\r\v><"))
					i++;
			}

			while (input[i] && ft_include(input[i], " \t\n\r\v"))
				i++;

			if (j > 0 && input[i] && res[j - 1] != ' ')
				res[j++] = ' ';
			continue ;
		}
		res[j++] = input[i++];
	}
	if (j > 0 && res[j - 1] == ' ')
		j--;
	res[j] = '\0';

	free(input);
	return (res);
}