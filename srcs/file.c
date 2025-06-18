/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:30:19 by gdalmass          #+#    #+#             */
/*   Updated: 2025/06/18 13:30:49 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	redir_to_file(t_chevron *stru, int (*fd)[2], int i, t_parser *info)
{
	if (stru->chevron == '<')
		stru->current_fd = &fd[i][0];
	else
		stru->current_fd = &fd[i][1];
	if (*stru->current_fd != -1 && *stru->current_fd != STDOUT_FILENO
		&& *stru->current_fd != STDIN_FILENO)
		close(*stru->current_fd);
	if (open_chevron_fd(*stru, info) == -1)
	{
		free(stru->start);
		free(stru->filename);
		return (-1);
	}
	free(stru->filename);
	return (1);
}

int	get_files(t_parser *info, int i, char **pipes)
{
	if (process_chevrons(pipes, i, info->fd, info) == -1)
	{
		info->fd[i][0] = -1;
		info->fd[i][1] = -1;
		return (-1);
	}
	return (1);
}

int	get_filename(t_chevron *stru, t_parser *info)
{
	stru->chevron = *stru->next_chevron;
	stru->tmp = stru->next_chevron + 1;
	stru->append = 0;
	parse_chevron_type(&stru->tmp, stru->chevron, info, &stru->append);
	stru->next_chevron = get_next_chevron(stru->tmp);
	stru->filename = extract_filename(stru->tmp);
	if (!stru->filename)
	{
		free(stru->start);
		return (-1);
	}
	return (1);
}
