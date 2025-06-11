/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:13:26 by quentin8340       #+#    #+#             */
/*   Updated: 2025/06/11 17:39:25 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_export(t_minish *manager, char *arg)
{
	char	**args;
	char	*trimmed;
	int		i;
	int		status;
	char	*equal;
	char	*key;
	char	*value;

	i = 0;
	status = 0;
	if (!arg || ft_strncmp(arg, "export", 6) == 0)
	{
		arg += 6;
		while (*arg == ' ')
			arg++;
	}
	args = split_args_preserving_quotes(arg);
	if (!args)
		return (1);
	while (args[i])
	{
		trimmed = strip_quotes(args[i]);
		if (!trimmed)
		{
			status = 1;
			i++;
			continue ;
		}
		equal = ft_strchr(trimmed, '=');
		if (equal)
		{
			key = ft_substr(trimmed, 0, equal - trimmed);
			value = ft_strdup(equal + 1);
			if (!is_valid_identifier(key))
			{
				ft_putstr_fd("minishell: export: `", 2);
				ft_putstr_fd(trimmed, 2);
				ft_putendl_fd("': not a valid identifier", 2);
				status = 1;
			}
			else
				set_env_key_value(manager, key, value);
			free(key);
			free(value);
		}
		else
		{
			if (!is_valid_identifier(trimmed))
			{
				ft_putstr_fd("minishell: export: `", 2);
				ft_putstr_fd(trimmed, 2);
				ft_putendl_fd("': not a valid identifier", 2);
				status = 1;
			}
			else
				set_env_key_value(manager, trimmed, NULL);
		}
		free(trimmed);
		i++;
	}
	free_split(args);
	manager->last_ex_code = status;
	return (status);
}
