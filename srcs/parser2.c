/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:15:38 by greg              #+#    #+#             */
/*   Updated: 2025/06/03 13:19:30 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_parser_struct(t_parser *info, char **pipes, int pipe_nb)
{
	int	i;

	i = 0;
	while (pipes[i])
		i++;
	info->cmd_nb = pipe_nb + 1;
	info->here_doc = 0;
	info->cmd = ft_calloc(i + 2, sizeof(char *));
}

void	clean_after_pipex(t_parser *info)
{
	if (info->fd[0] != STDIN_FILENO)
		close(info->fd[0]);
	if (info->fd[1] != STDOUT_FILENO)
		close(info->fd[1]);
	if (info->here_doc)
	{
		unlink("here_doc.txt");
		info->here_doc = 0;
	}
}

int	exec_pipex(int cmd_index, t_parser *info, t_minish *manager)
{
	int	i;
	int	code;

	if (info->cmd_nb == 1 && (!ft_strncmp(info->cmd[0], "export", 6) || !ft_strncmp(info->cmd[0], "unset", 5)))
	{
		if (!ft_strncmp(info->cmd[0], "export", 6))
			code = ft_export(&manager->envp, info->cmd[0]);
		else
			code = ft_unset(&manager->envp, info->cmd[0]);
	}
	else
		code = pipex(cmd_index, info->cmd, manager, info->fd);
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

int	is_builtins(char *str)
{
	if (!ft_strcmp(str, "pwd") || !ft_strcmp(str, "exit") || !ft_strcmp(str,
			"env") || !ft_strcmp(str, "cd") || !ft_strcmp(str, "echo")
		|| !ft_strcmp(str, "export") || !ft_strcmp(str, "unset"))
		return (1);
	return (0);
}

char	*sanitize_str(char *str)
{
	char	*trimmed;

	if (!str)
		return (NULL);
	trimmed = ft_strtrim(str, " \t\n\v\f\r");
	free(str);
	if (!trimmed)
		return (NULL);
	return (trimmed);
}
