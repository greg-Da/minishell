/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:55:49 by qbaret            #+#    #+#             */
/*   Updated: 2025/06/24 14:37:04 by gdalmass         ###   ########.fr       */
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

sig_atomic_t	*g_is_in_execution(void)
{
	static sig_atomic_t	variable;

	return (&variable);
}

int	handle_sig(char *trimmed, t_parser *info)
{
	int	tmp;

	free(trimmed);
	tmp = g_sig + 128;
	clean_after_pipex(info);
	return (tmp);
}
