/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:15:38 by greg              #+#    #+#             */
/*   Updated: 2025/06/03 12:46:47 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_handle_cmd(t_parser *info)
{
	int	j;

	j = -1;
	while (info->cmd[++j])
		free(info->cmd[j]);
	free(info->cmd);
	if (info->fd[0] != STDIN_FILENO)
		close(info->fd[0]);
	if (info->fd[1] != STDOUT_FILENO)
		close(info->fd[1]);
	info->fd[0] = STDIN_FILENO;
	info->fd[1] = STDOUT_FILENO;
	info->fd[2] = 0;
}

void	get_cmd(t_parser *info, char *pipe, int j)
{
	char	*cmd;
	char	*start;
	char	*end;
	char	*part;
	char	*tmp;

	cmd = NULL;
	start = pipe;
	while (*start)
	{
		while (*start && *start == ' ')
			start++;
		if (*start == '\0')
			break ;
		if (*start == '>' || *start == '<')
		{
			start++;
			if (*start == '>' || *start == '<')
				start++;
			while (*start && *start == ' ')
				start++;
			while (*start && *start != ' ' && *start != '>' && *start != '<')
				start++;
			continue ;
		}
		end = start;
		while (*end && *end != '>' && *end != '<')
			end++;
		part = ft_substr(start, 0, end - start);
		if (!part)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		if (cmd)
		{
			tmp = ft_strjoin(cmd, part);
			free(cmd);
			free(part);
			cmd = tmp;
		}
		else
			cmd = part;
		start = end;
	}
	if (!cmd)
		cmd = ft_strdup("");
	info->cmd[j] = sanitize_str(cmd);
	if (!info->cmd[j])
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
}

static int	handle_pipe_failure(t_parser *info, char *trimmed)
{
	free(trimmed);
	clean_handle_cmd(info);
	return (2);
}
static void	reset_parser_fds(t_parser *info)
{
	info->fd[0] = STDIN_FILENO;
	info->fd[1] = STDOUT_FILENO;
	info->fd[2] = 0;
}

static int	process_single_pipe(t_parser *info, char **pipes, t_minish *manager,
		int *cmd_index, int pipe_index)
{
	char	*pipe_copy;
	char	*trimmed;

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
	if (get_files(info, pipe_index, pipes) == -1)
		return (handle_pipe_failure(info, trimmed));
	get_cmd(info, pipes[pipe_index], *cmd_index);
	(*cmd_index)++;
	if (ft_strchr(pipes[pipe_index], '>'))
	{
		info->res = exec_pipex(*cmd_index, info, manager);
		*cmd_index = 0;
		reset_parser_fds(info);
	}
	free(trimmed);
	return (0);
}


int	parser(char **pipes, t_minish *manager, int pipe_nb)
{
	t_parser	info;
	int			pipe_index;
	int			cmd_index;

	pipe_index = 0;
	cmd_index = 0;
	init_parser_struct(&info, pipes, pipe_nb);
	reset_parser_fds(&info);
	
	while (pipes[pipe_index])
	{
		info.res = process_single_pipe(&info, pipes, manager, &cmd_index,
				pipe_index);
		if (info.res)
			return (info.res);
		pipe_index++;
	}
	if (cmd_index > 0)
		info.res = exec_pipex(cmd_index, &info, manager);
	
	clean_handle_cmd(&info);
	return (info.res);
}
