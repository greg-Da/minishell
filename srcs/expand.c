/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:50:26 by quentin           #+#    #+#             */
/*   Updated: 2025/06/05 11:43:11 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand_variable(char *var_name, t_minish *manager)
{
	char	*value;
	int i = -1;

	value = NULL;

	while (manager->envp[++i] != NULL)
	{
		if (ft_strncmp(manager->envp[i], var_name, ft_strlen(var_name)) == 0
			&& manager->envp[i][ft_strlen(var_name)] == '=')
		{
			value = manager->envp[i] + ft_strlen(var_name) + 1;
			break;
		}
	}
	
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

void	expand_all_args(char **args, t_minish *manager)
{
	int		i;
	char	*expanded;

	i = 0;
	while (args && args[i])
	{
		expanded = expand_string(args[i], manager);
		free(args[i]);
		args[i] = expanded;
		i++;
	}
}

char	*expand_string(char *input, t_minish *manager)
{
	char	result[2048] = {0};
	char	var_name[256] = {0};
	char	*var_value;
	int		i, j, k;
	size_t	len;

	i = 0, j = 0, k = 0;
	while (input[i])
	{
		if (input[i] == '$' && !is_between_quotes(input, i, '\''))
		{
			i++;
			if (input[i] == '?')
			{
				var_value = ft_itoa(manager->last_ex_code);
				if (var_value)
				{
					len = ft_strlen(var_value);
					if ((size_t)(j + len) < sizeof(result))
						ft_strlcpy(result + j, var_value, sizeof(result) - j);
					j += len;
					free(var_value);
				}
				i++;
			}
			else if (ft_isalpha(input[i]) || input[i] == '_')
			{
				k = 0;
				while ((ft_isalnum(input[i]) || input[i] == '_') && k < 255)
					var_name[k++] = input[i++];
				var_name[k] = '\0';
				var_value = expand_variable(var_name, manager);
				if (var_value)
				{
					len = ft_strlen(var_value);
					if ((size_t)(j + len) < sizeof(result))
						ft_strlcpy(result + j, var_value, sizeof(result) - j);
					j += len;
					free(var_value);
				}
			}
			else
			{
				if ((size_t)(j + 1) < sizeof(result))
					result[j++] = '$';
				if (input[i] && (size_t)(j + 1) < sizeof(result))
					result[j++] = input[i++];
			}
		}
		else
		{
			if ((size_t)(j + 1) < sizeof(result))
				result[j++] = input[i++];
		}
	}
	result[j] = '\0';
	return (ft_strdup(result));
}
