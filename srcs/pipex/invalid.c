/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:55:24 by greg              #+#    #+#             */
/*   Updated: 2025/06/11 17:32:05 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_executable(const char *path)
{
	struct stat	sb;

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
		ft_putstr_fd(": Is a directory\n", 2);
		return (126);
	}
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
	if (pipex && pipex->cmd_args && pipex->cmd_args[prev->i]
		&& pipex->cmd_args[prev->i][0])
	{
		if (strchr(pipex->cmd_args[prev->i][0], '/'))
			valid_file = is_valid_executable(pipex->cmd_args[prev->i][0]);
		if (valid_file > 0)
		{
			close(pipex->fd[1]);
			pipex->exit_code = valid_file;
			return ;
		}
		pipex->exit_code = 127;
		tmp = ft_strjoin(pipex->cmd_args[prev->i][0], ": command not found");
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd("\n", 2);
		free(tmp);
	}
	close(pipex->fd[1]);
}
