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

void default_std(int *std)
{
	dup2(std[0], STDIN_FILENO);
	dup2(std[1], STDOUT_FILENO);
	close(std[0]);
	close(std[1]);
}

void handle_exec_fail(int *std, int i, t_pipex *pip, t_prev prev)
{
	default_std(std);
	(void)i;
	// if (pip->cmd_path[i] == NULL)
	// 	exit(127);
	ft_invalid_cmd(pip, &prev);
	exit(pip->exit_code);
}

void ft_exec_child(t_prev prev, t_pipex *pip, int i, char **envp)
{
	int std[2];

	std[0] = dup(STDIN_FILENO);
	std[1] = dup(STDOUT_FILENO);

	// printf("prev.in: %d\n", prev.in);
	if (pip->in_fd != STDIN_FILENO && pip->in_fd != -1)
	{
		dup2(pip->in_fd, STDIN_FILENO);
		close(pip->in_fd);
	}
	else if (prev.in != STDIN_FILENO && prev.in != -1)
	{
		dup2(prev.in, STDIN_FILENO);
		close(prev.in);
	}
	else if (prev.in == -1 || pip->is_invalid_infile)
	{
		int devnull = open("/dev/null", O_RDONLY);
		if (devnull == -1)
			exit(1);
		dup2(devnull, STDIN_FILENO);
		close(devnull);
	}

	if (prev.out != STDOUT_FILENO && prev.out != -1)
	{
		dup2(prev.out, STDOUT_FILENO);
		close(prev.out);
	}

	if (prev.out == -1)
		exit(1);

	if (is_builtins(pip->cmd_args[i][0]))
	{
		if (!ft_strncmp(pip->cmd_args[i][0], "pwd", 3))
			pwd(pip->manager);
		else if (!ft_strncmp(pip->cmd_args[i][0], "env", 3))
			ft_env(pip);
		else if (!ft_strncmp(pip->cmd_args[i][0], "echo", 4))
			ft_echo(pip->cmd_args[i]);
		default_std(std);
		exit(0);
	}
	if (execve(pip->cmd_path[i], pip->cmd_args[i], envp) == -1)
		handle_exec_fail(std, i, pip, prev);
}

void ft_exec(t_prev prev, t_pipex *pip, int i, char **envp)
{
	pid_t pid;

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

void ft_manage_exec(t_pipex *pipex, t_prev *prev, char **envp)
{
	if (prev->i == pipex->cmd_count - 1)
		prev->out = pipex->out_fd;
	else
		prev->out = pipex->fd[1];
	ft_exec(*prev, pipex, prev->i, envp);
}

void ft_loop(t_pipex *pipex, t_prev *prev, char **envp)
{
	while (++prev->i < pipex->cmd_count)
	{
		pipex->exit_code = 0;
		if (pipex->cmd_args[prev->i][0] == NULL)
			continue;
		if (pipe(pipex->fd) == -1)
			ft_error("pipe failed");

		if (prev->i == 0 && !ft_strncmp(pipex->cmd_args[prev->i][0],
										"exit", 4))
		{
			if (pipex->cmd_args[prev->i + 1] == NULL)
				pipex->exit = 1;
			else
			{
				close(pipex->fd[1]);
				close(pipex->fd[0]);
				continue;
			}
		}
		// if (prev->in == -1)
		// {
		// 	// printf("minishell: %s: No such file or o\n",
		// 	//    pipex->cmd_args[prev->i][0]);
		// 	// ft_invalid_infile(pipex, prev);
		// 	printf("cmd: %s\n", pipex->cmd_args[prev->i][0]);
		// 	close(pipex->fd[1]);
		// 	close(pipex->fd[0]);
		// 	printf("prev->in: %d\n", prev->in);
		// }

		if (pipex->cmd_path[prev->i] == NULL && !is_builtins(pipex->cmd_args[prev->i][0]))
		{
			ft_invalid_cmd(pipex, prev);
			prev->in = pipex->fd[0];
			close(pipex->fd[1]);
			continue;
		}
		else if (!ft_strncmp(pipex->cmd_args[prev->i][0], "cd", 2))
			pipex->exit_code = ft_cd(pipex->cmd_args[prev->i], pipex->manager);
		else
		{
			ft_manage_exec(pipex, prev, envp);
		}
		close(pipex->fd[1]);
		if (prev->in != pipex->in_fd)
			close(prev->in);
		prev->in = pipex->fd[0];
		if (pipex->exit)
			break;
	}
}
