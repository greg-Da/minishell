/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:15:38 by greg              #+#    #+#             */
/*   Updated: 2025/06/11 17:36:29 by quentin8340      ###   ########.fr       */
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
		if ((*start == '>' || *start == '<') && !is_between_any_quotes(pipe,
				start - pipe))
		{
			start++;
			if ((*start == '>' || *start == '<') && !is_between_any_quotes(pipe,
					start - pipe))
				start++;
			while (*start && *start == ' ')
				start++;
			while (*start && *start != ' ' && ((*start != '>' && *start != '<')
					|| is_between_any_quotes(pipe, start - pipe)))
				start++;
			continue ;
		}
		end = start;
		while (*end && ((*end != '>' && *end != '<')
				|| !is_between_any_quotes(pipe, start - pipe)))
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
