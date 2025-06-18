/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:07:45 by greg              #+#    #+#             */
/*   Updated: 2025/06/18 14:23:05 by qbaret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_pwd(char *pwd, char *old_pwd, t_minish *manager)
{
	char	*str1;
	char	*str2;

	if (!pwd || !old_pwd)
		return ;
	str1 = ft_strjoin("PWD=", pwd);
	str2 = ft_strjoin("OLDPWD=", old_pwd);
	ft_export(manager, str2);
	ft_export(manager, str1);
	free(str1);
	free(str2);
}

int	handle_go_back(char *cur, t_minish *manager)
{
	char	*oldpwd;

	oldpwd = expand_string("$OLDPWD", manager);
	if (!oldpwd)
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
	if (chdir(oldpwd) == 0)
	{
		update_pwd(oldpwd, cur, manager);
		pwd(manager);
		free(oldpwd);
		return (0);
	}
	else
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
}

int	get_home(t_minish *manager)
{
	char	*home;

	home = expand_string("$HOME", manager);
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	if (chdir(home) != 0)
	{
		perror("cd");
		free(home);
		return (1);
	}
	free(home);
	return (0);
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

int	handle_default(char **path, char *pwd, t_minish *manager)
{
	char	*new_pwd;
	char	*tmp;
	int		status;

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

int	ft_cd(char **path, t_minish *manager)
{
	char	*pwd;
	int		status;

	if (path[1] != NULL && path[2] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	pwd = expand_string("$PWD", manager);
	status = handle_special(path, manager, pwd);
	if (status != -1)
		return (status);
	if (chdir(path[1]) == 0)
		status = handle_default(path, pwd, manager);
	else
	{
		perror("cd");
		status = 1;
		free(pwd);
		return (1);
	}
	free(pwd);
	manager->last_ex_code = status;
	return (0);
}
