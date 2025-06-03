/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:07:45 by greg              #+#    #+#             */
/*   Updated: 2025/06/03 12:13:55 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_pwd(void)
{
	char	*pwd;

	printf("NEED TO BE UPDATED WITH BUILTIN EXPORT/UNSET\n");
	pwd = getcwd(NULL, 0);
	if (!pwd)
		ft_putstr_fd("cd: PWD not set\n", 2);
	setenv("OLDPWD", getenv("PWD"), 1);
	setenv("PWD", pwd, 1);
	free(pwd);
}

int	handle_go_back(void)
{
	char	*oldpwd;

	oldpwd = getenv("OLDPWD");
	if (!oldpwd)
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
	if (chdir(oldpwd) == 0)
	{
		update_pwd();
		pwd();
		return (0);
	}
	else
	{
		perror("cd");
		return (1);
	}
}

int	get_home(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	if (chdir(home) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	ft_cd(char **path)
{
	if (path[1] != NULL && path[2] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return(126);
	}
	else if (path[1] == NULL || !ft_strcmp(path[1], "~"))
	return (get_home());
	else if (!ft_strcmp(path[1], "-"))
		return (handle_go_back());
	else
	{
		if (chdir(path[1]) == 0)
			update_pwd();
		else
		{
			perror("cd");
			return (1);
		}
	}
	return (0);
}