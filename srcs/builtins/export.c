/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:13:26 by quentin8340       #+#    #+#             */
/*   Updated: 2025/06/05 17:29:17 by qbaret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return;
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
	int		i = 0;
	int		status = 0;

	if (ft_strncmp(arg, "export", 6) == 0)
	{
		arg += 6;
		while (*arg == ' ')
			arg++;
	}

	args = ft_split(arg, ' ');
	if (!args)
		return (1);

	while (args[i])
	{
		trimmed = remove_double_quotes(args[i]);
		if (!trimmed)
		{
			status = 1;
			i++;
			continue;
		}

		char *assign = ft_strchr(trimmed, '=');
		if (!assign || assign == trimmed)
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(trimmed, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			free(trimmed);
			status = 1;
			i++;
			continue;
		}

		char *key = ft_substr(trimmed, 0, assign - trimmed);
		char *value = ft_strdup(assign + 1);

		if (!is_valid_identifier(key))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(key, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = 1;
		}
		else
			set_env_key_value(manager, key, value);

		free(key);
		free(value);
		free(trimmed);
		i++;
	}

	free_split(args);
	manager->last_ex_code = status;
	return (status);
}



