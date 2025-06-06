/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:54:38 by gdalmass          #+#    #+#             */
/*   Updated: 2025/06/06 19:15:10 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_cleanup(t_pipex *pipex)
{
	int	i;
	int	j;

	// close(pipex.in_fd);
	// close(pipex.out_fd);
	free(pipex->pids);
	// if (pipex->here_doc)
	// 	unlink("here_doc.txt");
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

void	ft_wait_children(t_pipex *pipex, t_prev prev, int i)
{
	int	status;

	while (pipex->pids_size > ++i)
	{
		waitpid(pipex->pids[i], &status, 0);
		if (WEXITSTATUS(status))
		{
			if (pipex->pids_size - 1 == i)
				pipex->exit_code = WEXITSTATUS(status);
		}
		if (prev.out == -1)
		{
			pipex->exit_code = 1;
		}
	}
}

int	pipex(int nmb, char **cmd, t_minish *manager, int *fd)
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
	pipex.in_fd = fd[0];
	pipex.out_fd = fd[1];
	pipex.is_invalid_infile = fd[2];
	ft_init_struct(&pipex, nmb, cmd, manager);
	prev.in = pipex.in_fd;
	prev.i = -1;
	ft_loop(&pipex, &prev, pipex.envp);
	i = -1;
	ft_wait_children(&pipex, prev, i);
	ft_cleanup(&pipex);
	return (pipex.exit_code);
}
