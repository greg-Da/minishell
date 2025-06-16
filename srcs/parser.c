/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:15:38 by greg              #+#    #+#             */
/*   Updated: 2025/06/16 12:42:10 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	reset_parser_fds(t_parser *info)
{
	int	i;

	i = -1;
	while (++i < info->cmd_nb)
	{
		if (info->fd[i][0] != STDIN_FILENO)
			close(info->fd[i][0]);
		if (info->fd[i][1] != STDOUT_FILENO)
			close(info->fd[i][1]);
	}
	free(info->fd);
}

void	clean_handle_cmd(t_parser *info)
{
	int	j;

	j = -1;
	while (info->cmd[++j])
		free(info->cmd[j]);
	free(info->cmd);
}

void	get_cmd(t_parser *info, char *pipe, int j)
{
	info->cmd[j] = sanitize_str(ft_strdup(pipe));
	info->cmd[j] = skip_redir_and_filename(info->cmd[j]);
	if (!info->cmd[j])
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
}

static int	process_single_pipe(t_parser *info, char **pipes, t_minish *manager,
		int *cmd_index, int pipe_index)
{
	char	*pipe_copy;
	char	*trimmed;

	(void)manager;
	pipe_copy = ft_strdup(pipes[pipe_index]);
	if (!pipe_copy)
	{
		clean_handle_cmd(info);
		return (1);
	}
	trimmed = sanitize_str(pipe_copy);
	if (!trimmed)
	{
		clean_handle_cmd(info);
		return (1);
	}
	get_files(info, pipe_index, pipes);
	get_cmd(info, pipes[pipe_index], *cmd_index);
	(*cmd_index)++;
	free(trimmed);
	return (info->res);
}

int	parser(char **pipes, t_minish *manager, int pipe_nb)
{
	t_parser	info;
	int			pipe_index;
	int			cmd_index;

	pipe_index = 0;
	cmd_index = 0;
	init_parser_struct(&info, manager, pipes, pipe_nb);
	while (pipes[pipe_index])
	{
		info.res = process_single_pipe(&info, pipes, manager, &cmd_index,
				pipe_index);
		pipe_index++;
	}
	if (cmd_index > 0)
		info.res = exec_pipex(cmd_index, &info, manager);
	clean_handle_cmd(&info);
	return (info.res);
}
