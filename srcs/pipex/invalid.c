/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:55:24 by greg              #+#    #+#             */
/*   Updated: 2025/06/06 11:33:14 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_executable(const char *path)
{
	struct stat	sb;

	// Check if the file exists
	if (access(path, F_OK) != 0)
	{
		perror(path);
		return (127);
	}
	if (stat(path, &sb) != 0)
	{
		perror("stat failed");
		return (127);
	}
	if (S_ISDIR(sb.st_mode))
	{
		ft_putstr_fd((char *)path, 2);
		ft_putstr_fd(": is a directory.\n", 2);
		return (126);
	}
	// Check if it's executable
	if (access(path, X_OK) != 0)
	{
		perror(path);
		return (126);
	}
	return (0);
}

void	ft_invalid_cmd(t_pipex *pipex, t_prev *prev)
{
	char	*tmp;
	int		valid_file;

	valid_file = 0;
	if (strchr(pipex->cmd_args[prev->i][0], '/'))
		valid_file = is_valid_executable(pipex->cmd_args[prev->i][0]);
	if (valid_file > 0)
		pipex->exit_code = valid_file;
	else if (prev->i == pipex->cmd_count - 1)
	{
		pipex->exit_code = 127;
		tmp = ft_strjoin(pipex->cmd_args[prev->i][0], ": command not found");
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd("\n", 2);
		free(tmp);
	}
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
