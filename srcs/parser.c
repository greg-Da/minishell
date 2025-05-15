/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:15:38 by greg              #+#    #+#             */
/*   Updated: 2025/03/10 15:44:11 by greg             ###   ########.fr       */
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
}

int	get_files(t_parser *info, int i, int j, char **pipes)
{
	info->files[0] = NULL;
	info->files[1] = NULL;
	info->chevron = get_chevron_indices(pipes[i], info->index);
	if (info->chevron)
		info->index[1] = info->chevron - pipes[i];
	else
		info->index[1] = ft_strlen(pipes[i]);
	j = get_infile(info, pipes, i, j);
	if (get_outfile(info, pipes, i) == -1)
		return (-1);
	return (j);
}

void	get_cmd(t_parser *info, char **pipes, int i, int j)
{
	if (info->index[0] != 0)
		info->cmd[j] = sanitize_str(ft_substr(pipes[i], 0, info->index[0]));
	else
		info->cmd[j] = sanitize_str(ft_substr(pipes[i], 0, info->index[1]));
}

int	parser(char **pipes, char **envp, int pipe_nb)
{
	t_parser	info;
	int			i;
	int			j;

	init_parser_struct(&info, pipes, pipe_nb);
	i = 0;
	j = 0;
	while (pipes[i])
	{
		j = get_files(&info, i, j, pipes);
		if (j == -1)
		{
			free(info.cmd);
			return (2);
		}
		get_cmd(&info, pipes, i, j);
		j++;
		if (info.chevron)
			info.res = exec_pipex(&j, &info, envp);
		i++;
		if (info.files[0])
			free(info.files[0]);
		if (info.files[1])
			free(info.files[1]);
	}
	info.fd[1] = STDOUT_FILENO;
	if (!info.chevron)
		info.res = pipex(j, info.cmd, envp, info.fd);
	clean_handle_cmd(&info);
	return (info.res);
}

int	get_pipe_count(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '|')
			count++;
		i++;
	}
	return (count);
}

int	handle_cmd(char **envp, t_minish *manager)
{
	char	*input;
	char	**pipes;
	int		i;
	int		code;

	input = readline(">  ");
	if (*input && ft_strcmp(input, manager->last_cmd) != 0)
		add_history(input);
	
	
		// TO DO : ENV VAR + $?

	pipes = ft_split(input, '|');
	code = parser(pipes, envp, get_pipe_count(input));
	i = 0;
	while (pipes[i])
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
	free(input);
	return (code);
}
