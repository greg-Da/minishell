/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:13:26 by quentin8340       #+#    #+#             */
/*   Updated: 2025/06/04 15:08:38 by quentin8340      ###   ########.fr       */
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
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	update_env(t_minish *manager, char *arg)
{
	int		i;
	size_t	len;
	char	*var_name;
	char	**new_env;

	len = 0;
	while (arg[len] && arg[len] != '=')
	{
		if (arg[len] == ' ')
			return ;
		len++;
	}
	var_name = ft_substr(arg, 0, len);
	if (!var_name)
		return ;
	i = 0;
	while (manager->envp[i])
	{
		if (ft_strncmp(manager->envp[i], var_name, len) == 0 &&
			(manager->envp[i][len] == '\0' || manager->envp[i][len] == '='))
		{
			free(manager->envp[i]);
			manager->envp[i] = ft_strdup(arg);
			free(var_name);
			return ;
		}
		i++;
	}
	new_env = ft_realloc_env(manager->envp, arg);
	if (!new_env)
	{
		free(var_name);
		return ;
	}
	i = 0;
	while (manager->envp[i])
		free(manager->envp[i++]);
	free(manager->envp);

	manager->envp = new_env;
	free(var_name);
}

int	ft_export(t_minish *manager, char *arg)
{
	char	**args;
	char	*trimmed;
	int		i;
	int		status;

	args = ft_split(arg + 6, ' ');
	if (!args)
		return (1);
	i = 0;
	status = 0;
	while (args[i])
	{
		trimmed = ft_strtrim(args[i], " \f\t\n\r\v");
		if (!trimmed)
		{
			status = 1;
			i++;
			continue;
		}
		if (!is_valid_identifier(trimmed))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(trimmed, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = 1;
		}
		else
			update_env(manager, trimmed);
		free(trimmed);
		i++;
	}
	free_split(args);
	manager->last_ex_code = status;
	return (status);
}

