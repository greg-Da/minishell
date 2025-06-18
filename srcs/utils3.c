/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:55:49 by qbaret            #+#    #+#             */
/*   Updated: 2025/06/18 16:57:58 by qbaret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	default_std(int *std)
{
	dup2(std[0], STDIN_FILENO);
	dup2(std[1], STDOUT_FILENO);
	close(std[0]);
	close(std[1]);
}

void	handle_exec_fail(int *std, int i, t_pipex *pip, t_prev prev)
{
	default_std(std);
	(void)i;
	ft_invalid_cmd(pip, &prev);
	exit(pip->exit_code);
}
