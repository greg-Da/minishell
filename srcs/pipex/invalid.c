/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:55:24 by greg              #+#    #+#             */
/*   Updated: 2025/03/10 13:55:38 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_invalid_cmd(t_pipex *pipex, t_prev *prev)
{
	char	*tmp;

	if (prev->i == pipex->cmd_count - 1)
		pipex->exit_code = 127;
	tmp = ft_strjoin(pipex->cmd_args[prev->i][0], ": command not found");
	ft_putstr_fd(tmp, 2);
	ft_putstr_fd("\n", 2);
	free(tmp);
	close(pipex->fd[1]);
}

int	ft_invalid_infile(t_pipex *pipex, t_prev *prev)
{
	if (pipex->is_invalid_infile == 1)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		if (prev->i == pipex->cmd_count - 1)
			write(pipex->out_fd, "\0", 1);
		else
			write(pipex->fd[1], "\0", 1);
	}
	else
	{
		close(pipex->fd[1]);
		close(pipex->fd[0]);
		return (-1);
	}
	return (0);
}
