/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:07:45 by greg              #+#    #+#             */
/*   Updated: 2025/06/04 15:36:09 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void update_pwd(char *pwd, char *old_pwd, t_minish *manager)
{
	char *tmp;

	if (pwd == NULL || old_pwd == NULL)
		return;

	tmp = ft_strjoin("export OLDPWD=", old_pwd);
	ft_export(manager, tmp);
	free(tmp);

	tmp = ft_strjoin("export PWD=", pwd);
	ft_export(manager, tmp);
	free(tmp);
}

int handle_go_back(char *cur, t_minish *manager)
{
	char *oldpwd;

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

int get_home(t_minish *manager)
{
	char *home;

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

void get_logical_parent(char *pwd, t_minish *manager)
{
	char *copy = ft_strdup(pwd);
	char *last_slash = NULL;
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

int ft_cd(char **path, t_minish *manager)
{
	char *pwd;
	char *new_pwd;

	if (path[1] != NULL && path[2] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (126);
	}

	pwd = expand_string("$PWD", manager);

	if (path[1] == NULL || !ft_strcmp(path[1], "~"))
	{
		get_home(manager);
		new_pwd = getcwd(NULL, 0);
		update_pwd(new_pwd, pwd, manager);
		free(pwd);
		free(new_pwd);
		return (0);
	}
	else if (!ft_strcmp(path[1], "-"))
	{
		handle_go_back(pwd, manager);
		free(pwd);
		return (0);
	}
	else
	{
		if (chdir(path[1]) == 0)
		{
			new_pwd = getcwd(NULL, 0);

			if (!new_pwd)
			{
				if (!ft_strcmp(path[1], "..") && pwd[ft_strlen(pwd - 1)] == '.' && pwd[ft_strlen(pwd - 2)] == '.')
					get_logical_parent(pwd, manager);
				else if (!ft_strcmp(path[1], ".."))
				{
					char *tmp = ft_strjoin(pwd, "/..");
					update_pwd(tmp, pwd, manager);
					free(tmp);
					perror("cd: error retrieving current directory: getcwd: cannot access parent directories");
				}
				else
					perror("getcwd");
			}
			update_pwd(new_pwd, pwd, manager);
			free(new_pwd);
		}
		else
		{
			perror("cd");
			free(pwd);
			return (1);
		}
	}
	free(pwd);
	return (0);
}