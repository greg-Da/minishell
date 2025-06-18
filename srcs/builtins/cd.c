/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:07:45 by greg              #+#    #+#             */
/*   Updated: 2025/06/18 15:16:10 by qbaret           ###   ########.fr       */
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
		status = handle_default(path, pwd, status, manager);
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
