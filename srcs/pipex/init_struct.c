/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:42:37 by gdalmass          #+#    #+#             */
/*   Updated: 2025/02/20 13:23:11 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_get_cmd_path(char **arr, char *cmd)
{
	int		i;
	char	*path;
	char	*tmp;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	i = 0;
	while (arr[i])
	{
		tmp = ft_strjoin("/", cmd);
		path = ft_strjoin(arr[i], tmp);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*ft_get_path_env(char **envp)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	if (!envp[i])
		return ("/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (!path)
		return ("");
	return (path);
}

void	ft_init_part2(t_pipex *pip, int nmb, char **cmd, char **envp)
{
	int		i;
	char	**path_arr;

	pip->cmd_count = nmb;
	path_arr = ft_split(ft_get_path_env(envp), ':');
	pip->cmd_args = malloc((pip->cmd_count + 1) * sizeof(char **));
	pip->cmd_path = malloc((pip->cmd_count + 1) * sizeof(char *));
	pip->cmd_args[pip->cmd_count] = NULL;
	pip->cmd_path[pip->cmd_count] = NULL;
	i = -1;
	while (++i < (pip->cmd_count))
	{
		pip->cmd_args[i] = ft_custom_split(cmd[i], 32, pip);
		pip->cmd_path[i] = ft_get_cmd_path(path_arr, pip->cmd_args[i][0]);
	}
	i = -1;
	while (path_arr[++i])
		free(path_arr[i]);
	free(path_arr);
}

void	ft_init_struct(t_pipex *pipex, int nmb, char **cmd, char **envp)
{
	pipex->here_doc = 0;
	if (pipex->in_fd == -10)
	{
		pipex->here_doc = 1;
		pipex->in_fd = open("here_doc.txt", O_RDWR | O_CREAT, 0666);
	}
	pipex->exit_code = 0;
	pipex->exit = 0;
	pipex->pids_size = 0;
	pipex->pids = malloc(sizeof(int));
	ft_init_part2(pipex, nmb, cmd, envp);
}
