/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:54:13 by greg              #+#    #+#             */
/*   Updated: 2025/05/29 17:5:28 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_builtins(t_pipex *pip, int i, int std[2])
{
	if (!ft_strncmp(pip->cmd_args[i][0], "pwd", 3))
		pwd(pip->manager);
	else if (!ft_strncmp(pip->cmd_args[i][0], "env", 3))
		ft_env(pip->envp, 0);
	else if (!ft_strncmp(pip->cmd_args[i][0], "echo", 4))
		ft_echo(pip->cmd_args[i]);
	default_std(std);
	exit(0);
}

void	handle_stdin(t_pipex *pip, t_prev prev)
{
	if (pip->fds[prev.i][0] != STDIN_FILENO)
	{
		if (pip->fds[prev.i][0] == -1)
			exit(1);
		dup2(pip->fds[prev.i][0], STDIN_FILENO);
		if (pip->fds[prev.i][0] != STDIN_FILENO)
			close(pip->fds[prev.i][0]);
	}
	else if (prev.in != STDIN_FILENO && prev.in != -1)
		dup2(prev.in, STDIN_FILENO);
}

void	handle_stdout(t_pipex *pip, t_prev prev, int std[2])
{
	if (pip->fds[prev.i][1] != STDOUT_FILENO)
	{
		if (pip->fds[prev.i][1] == -1)
		{
			default_std(std);
			exit(1);
		}
		dup2(pip->fds[prev.i][1], STDOUT_FILENO);
		if (pip->fds[prev.i][1] != STDOUT_FILENO)
			close(pip->fds[prev.i][1]);
	}
	else if (prev.out != STDOUT_FILENO)
		dup2(prev.out, STDOUT_FILENO);
}

void	ft_exec_child(t_prev prev, t_pipex *pip, int i, char **envp)
{
	int	std[2];

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	std[0] = dup(STDIN_FILENO);
	std[1] = dup(STDOUT_FILENO);
	handle_stdin(pip, prev);
	handle_stdout(pip, prev, std);
	if (prev.in != STDIN_FILENO)
		close(prev.in);
	if (prev.out != STDOUT_FILENO)
		close(prev.out);
	if (is_builtins(pip->cmd_args[i][0]))
		exec_builtins(pip, i, std);
	if (execve(pip->cmd_path[i], pip->cmd_args[i], envp) == -1)
		handle_exec_fail(std, i, pip, prev);
}

void	ft_exec(t_prev prev, t_pipex *pip, int i, char **envp)
{
	pid_t	pid;

	g_is_in_execution = 1;
	pid = fork();
	if (pid < 0)
		ft_error("fork failed");
	if (pid == 0)
	{
		close(pip->fd[0]);
		ft_exec_child(prev, pip, i, envp);
	}
	close(pip->fd[1]);
	pip->pids_size++;
	pip->pids = ft_realloc(pip->pids, (pip->pids_size) * sizeof(int),
			(pip->pids_size + 1) * sizeof(int));
	pip->pids[pip->pids_size - 1] = pid;
}
