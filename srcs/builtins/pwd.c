/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:24:18 by greg              #+#    #+#             */
/*   Updated: 2025/06/11 17:39:22 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd(t_minish *manager)
{
	char	*cwd;

	cwd = expand_string("$PWD", manager);
	if (cwd[0] == '\0')
	{
		free(cwd);
		cwd = getcwd(NULL, 0);
	}
	if (!cwd)
	{
		perror("getcwd");
		return (1);
	}
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(cwd);
	return (0);
}
