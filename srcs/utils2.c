/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:29:13 by gdalmass          #+#    #+#             */
/*   Updated: 2025/06/18 15:52:15 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	display_err(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
}

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
