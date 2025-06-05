/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:42:37 by gdalmass          #+#    #+#             */
/*   Updated: 2025/06/05 16:39:11 by qbaret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

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

void	ft_init_part2(t_pipex *pip, int nmb, char **cmd)
{
	int		i;
	char	**path_arr;

	if (!cmd || !*cmd)
	{
		pip->cmd_count = 0;
		pip->cmd_args = NULL;
		pip->cmd_path = NULL;
		return ;
	}
	pip->cmd_count = nmb;
	path_arr = ft_split(ft_get_path_env(pip->envp), ':');
	if (!path_arr)
		return ;
	pip->cmd_args = malloc((pip->cmd_count + 1) * sizeof(char **));
	if (!pip->cmd_args)
	{
		ft_free_array(path_arr);
		return ;
	}
	pip->cmd_path = malloc((pip->cmd_count + 1) * sizeof(char *));
	if (!pip->cmd_path)
	{
		free(pip->cmd_args);
		ft_free_array(path_arr);
		return ;
	}
	pip->cmd_args[pip->cmd_count] = NULL;
	pip->cmd_path[pip->cmd_count] = NULL;
	i = -1;
	while (++i < pip->cmd_count && cmd[i])
	{
		pip->cmd_args[i] = ft_custom_split(cmd[i], 32, pip->manager);
		if (pip->cmd_args[i] && pip->cmd_args[i][0])
			pip->cmd_path[i] = ft_get_cmd_path(path_arr, pip->cmd_args[i][0]);
		else
			pip->cmd_path[i] = NULL;
	}
	ft_free_array(path_arr);
}

void	ft_init_struct(t_pipex *pipex, int nmb, char **cmd, t_minish *manager)
{
	pipex->cmd_args = NULL;
	pipex->cmd_path = NULL;
	pipex->pids = NULL;
	pipex->manager = manager;
	pipex->exit_code = 0;
	pipex->exit = 0;
	pipex->pids_size = 0;
	pipex->pids = malloc(sizeof(int));
	pipex->envp = manager->envp;
	if (!pipex->pids)
		return ;
	ft_init_part2(pipex, nmb, cmd);
}
