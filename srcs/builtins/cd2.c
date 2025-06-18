/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:33:02 by qbaret            #+#    #+#             */
/*   Updated: 2025/06/18 15:14:56 by qbaret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_go_home(t_minish *manager, char *pwd)
{
	char	*new_pwd;

	if (get_home(manager) == 1)
		return (1);
	new_pwd = getcwd(NULL, 0);
	update_pwd(new_pwd, pwd, manager);
	free(pwd);
	free(new_pwd);
	return (0);
}

int	handle_special(char **path, t_minish *manager, char *pwd)
{
	if (path[1] == NULL || !ft_strcmp(path[1], "~"))
		return (handle_go_home(manager, pwd));
	else if (!ft_strcmp(path[1], "-"))
	{
		handle_go_back(pwd, manager);
		free(pwd);
		return (0);
	}
	return (-1);
}

int	handle_default(char **path, char *pwd, int status, t_minish *manager)
{
	char	*new_pwd;
	char	*tmp;

	status = 0;
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		if (!ft_strcmp(path[1], "..") && pwd[ft_strlen(pwd - 1)] == '.'
			&& pwd[ft_strlen(pwd - 2)] == '.')
			get_logical_parent(pwd, manager);
		else if (!ft_strcmp(path[1], ".."))
		{
			tmp = ft_strjoin(pwd, "/..");
			update_pwd(tmp, pwd, manager);
			free(tmp);
			perror("cd: error retrieving current directory");
			status = 1;
		}
		else
			perror("getcwd");
		status = 1;
	}
	update_pwd(new_pwd, pwd, manager);
	free(new_pwd);
	return (status);
}

void	get_logical_parent(char *pwd, t_minish *manager)
{
	char	*copy;
	char	*last_slash;

	copy = ft_strdup(pwd);
	last_slash = NULL;
	if (!copy)
		return ;
	while (chdir(copy) != 0)
	{
		last_slash = ft_strrchr(copy, '/');
		if (last_slash && last_slash != copy)
			*last_slash = '\0';
		else if (last_slash == copy)
			copy[1] = '\0';
	}
	update_pwd(copy, pwd, manager);
	free(copy);
}
