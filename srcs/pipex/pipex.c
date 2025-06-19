/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:54:38 by gdalmass          #+#    #+#             */
/*   Updated: 2025/06/19 14:53:14 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_cleanup(t_pipex *pipex)
{
	int	i;
	int	j;

	free(pipex->pids);
	i = -1;
	while (pipex->cmd_args && pipex->cmd_args[++i])
	{
		j = -1;
		free(pipex->cmd_path[i]);
		while (pipex->cmd_args[i][++j])
			free(pipex->cmd_args[i][j]);
		free(pipex->cmd_args[i]);
	}
	free(pipex->cmd_path);
	free(pipex->cmd_args);
}

void	ft_wait_children(t_pipex *pipex, int i)
{
	int	status;
	int	sig;

	while (pipex->pids_size > ++i)
	{
		waitpid(pipex->pids[i], &status, 0);
		if (pipex->pids_size - 1 == i)
			pipex->exit_code = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGQUIT)
			{
				write(2, "Quit (core dumped)\n", 20);
				pipex->exit_code = 131;
			}
		}
	}
	g_is_in_execution = 0;
}

int	pipex(int nmb, char **cmd, t_minish *manager, int (*fd)[2])
{
	t_pipex	pipex;
	t_prev	prev;
	int		i;

	i = 1;
	while (++i < nmb - 1)
	{
		if (ft_strlen(cmd[i]) == 0)
			exit(1);
	}
	ft_init_struct(&pipex, nmb, cmd, manager);
	pipex.fds = fd;
	prev.in = fd[0][0];
	prev.i = -1;
	ft_loop(&pipex, &prev, pipex.envp);
	i = -1;
	ft_wait_children(&pipex, i);
	ft_cleanup(&pipex);
	return (pipex.exit_code);
}
