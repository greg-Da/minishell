/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:13:26 by quentin8340       #+#    #+#             */
/*   Updated: 2025/06/19 14:15:13 by qbaret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	handle_export_key_only(t_minish *manager, char *arg, int *status)
{
	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		*status = 1;
	}
	else
		set_env_key_value(manager, arg, NULL);
}

void	handle_export_argument(t_minish *manager, char *trimmed, int *status)
{
	char	*equal;
	char	*key;
	char	*value;

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
			*status = 1;
		}
		else
			set_env_key_value(manager, key, value);
		free(key);
		free(value);
	}
	else
		handle_export_key_only(manager, trimmed, status);
}

void	process_export_args(t_minish *manager, char **args, int *status)
{
	char	*trimmed;
	int		i;

	i = 0;
	while (args[i])
	{
		trimmed = strip_quotes(args[i]);
		if (!trimmed)
		{
			*status = 1;
			i++;
			continue ;
		}
		handle_export_argument(manager, trimmed, status);
		free(trimmed);
		i++;
	}
}

int	ft_export(t_minish *manager, char *arg)
{
	char	**args;
	int		status;

	status = 0;
	if (!arg || ft_strncmp(arg, "export", 6) == 0)
	{
		arg += 6;
		while (*arg == ' ')
			arg++;
		if (*arg == '\0')
		{
			ft_env(manager->envp, 1);
			return (0);
		}
	}
	args = split_args_preserving_quotes(arg);
	if (!args)
		return (1);
	process_export_args(manager, args, &status);
	free_split(args);
	manager->last_ex_code = status;
	return (status);
}
