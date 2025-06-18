/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:17:58 by gdalmass          #+#    #+#             */
/*   Updated: 2025/06/18 15:42:02 by qbaret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exit_case(t_prev *prev, t_pipex *pipex)
{
	if (prev->i == 0 && !ft_strncmp(pipex->cmd_args[prev->i][0], "exit", 4))
	{
		if (pipex->cmd_args[prev->i + 1] == NULL)
			pipex->exit = 1;
		else
			return (1);
	}
	return (0);
}

void	ft_loop(t_pipex *pipex, t_prev *prev, char **envp)
{
	while (++prev->i < pipex->cmd_count)
	{
		pipex->exit_code = 0;
		if (exit_case(prev, pipex))
			continue ;
		if (pipe(pipex->fd) == -1)
			ft_error("pipe failed");
		if (pipex->cmd_path[prev->i] == NULL
			&& !is_builtins(pipex->cmd_args[prev->i][0]))
		{
			ft_invalid_cmd(pipex, prev);
			continue ;
		}
		else if (!ft_strncmp(pipex->cmd_args[prev->i][0], "cd", 2))
			pipex->exit_code = ft_cd(pipex->cmd_args[prev->i], pipex->manager);
		else
			ft_manage_exec(pipex, prev, envp);
		close(pipex->fd[1]);
		if (prev->in != STDIN_FILENO)
			close(prev->in);
		prev->in = pipex->fd[0];
		if (pipex->exit)
			break ;
	}
}
