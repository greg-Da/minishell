/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:24:18 by greg              #+#    #+#             */
/*   Updated: 2025/06/04 15:28:17 by greg             ###   ########.fr       */
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
