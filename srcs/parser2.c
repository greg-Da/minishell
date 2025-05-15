/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:15:38 by greg              #+#    #+#             */
/*   Updated: 2025/03/13 14:40:13 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_valid_file(t_parser *info, int i, int cmd_index)
{
	if (info->files[i][0] == '\0')
	{
		if (info->cmd_nb == cmd_index + 1)
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
				STDERR_FILENO);
		else
			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
				STDERR_FILENO);
		return (0);
	}
	return (1);
}

int	get_infile(t_parser *info, char **pipes, int i, int j)
{
	if (info->index[0])
	{
		if (info->fd[0] != STDIN_FILENO)
			close(info->fd[0]);
		if (pipes[i][info->index[0] + 1] == '<')
		{
			info->fd[0] = -10;
			info->cmd[j] = sanitize_str(ft_substr(pipes[i], info->index[0] + 2,
						info->index[1]));
			j++;
		}
		else
		{
			info->files[0] = sanitize_str(ft_substr(pipes[i], info->index[0]
						+ 1, info->index[1]));
			if (check_valid_file(info, 0, i) == 0)
				return (-1);
			info->fd[0] = open(info->files[0], O_RDONLY);
			if (info->fd[0] == -1)
			{
				if (access(info->files[0], F_OK) != 0)
					info->fd[2] = 1;
				else
					info->fd[2] = 2;
			}
		}
	}
	return (j);
}

int	get_outfile(t_parser *info, char **pipes, int i)
{
	if (info->index[1] != (int)ft_strlen(pipes[i]))
	{
		if (pipes[i][info->index[1] + 1] == '>')
		{
			info->files[1] = ft_strtrim(info->chevron + 2, " ");
			info->fd[1] = ft_create_outfile(1, info->files[1]);
		}
		else
		{
			info->files[1] = ft_strtrim(info->chevron + 1, " ");
			if (check_valid_file(info, 1, i) == 0)
				return (-1);
			info->fd[1] = ft_create_outfile(0, info->files[1]);
		}
	}
	else
	{
		info->fd[1] = STDOUT_FILENO;
	}
	return (1);
}

void	init_parser_struct(t_parser *info, char **pipes, int pipe_nb)
{
	int	i;

	i = 0;
	info->fd[0] = STDIN_FILENO;
	info->fd[1] = STDOUT_FILENO;
	info->fd[2] = 0;
	while (pipes[i])
		i++;
	info->cmd_nb = pipe_nb;
	info->cmd = ft_calloc(i + 2, sizeof(char *));
}

void	clean_after_pipex(t_parser *info)
{
	if (info->fd[0] != STDIN_FILENO)
		close(info->fd[0]);
	if (info->fd[1] != STDOUT_FILENO)
		close(info->fd[1]);
	info->fd[0] = open(info->files[1], O_RDWR);
}

int	exec_pipex(int *j, t_parser *info, char **envp)
{
	int	i;
	int	code;

	code = pipex(*j, info->cmd, envp, info->fd);
	*j = 0;
	clean_after_pipex(info);
	i = 0;
	while (info->cmd[i])
	{
		free(info->cmd[i]);
		info->cmd[i] = NULL;
		i++;
	}
	return (code);
}
