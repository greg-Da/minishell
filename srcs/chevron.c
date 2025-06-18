/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevron.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:08:00 by greg              #+#    #+#             */
/*   Updated: 2025/06/17 14:12:09 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	parse_chevron_type(char **tmp, char chevron, t_parser *info,
		int *append)
{
	if (**tmp == chevron && chevron == '>')
	{
		*append = 1;
		(*tmp)++;
	}
	else if (**tmp == chevron && chevron == '<')
	{
		if (info->here_doc)
			unlink("here_doc.txt");
		(*tmp)++;
		info->here_doc = 1;
	}
	while (**tmp && **tmp == ' ')
		(*tmp)++;
	return (0);
}

char	*get_next_chevron(char *str)
{
	int		i;
	char	*first;

	first = NULL;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '>' || str[i] == '<') && !is_between_char(str, i, '\'')
				&& !is_between_char(str, i, '\"'))
		{
			first = &str[i];
			break ;
		}
		i++;
	}
	return (first);
}

int	process_chevrons(char **pipes, int i, int (*fd)[2], t_parser *info)
{
	t_chevron	stru;

	stru.tmp = ft_strdup(pipes[i]);
	if (!stru.tmp)
		return (-1);
	stru.start = stru.tmp;
	stru.next_chevron = get_next_chevron(stru.tmp);
	fd[i][0] = STDIN_FILENO;
	fd[i][1] = STDOUT_FILENO;
	while (stru.next_chevron)
	{
		stru.chevron = *stru.next_chevron;
		stru.tmp = stru.next_chevron + 1;
		stru.append = 0;
		parse_chevron_type(&stru.tmp, stru.chevron, info, &stru.append);
		stru.next_chevron = get_next_chevron(stru.tmp);
		stru.filename = extract_filename(stru.tmp);
		if (!stru.filename)
			return (free(stru.start), -1);
		if (!stru.filename[0])
		{
			free(stru.filename);
			return (handle_filename_error(pipes, i, stru.tmp, stru.start));
		}
		stru.current_fd = (stru.chevron == '<') ? &fd[i][0] : &fd[i][1];
		if (*stru.current_fd != -1 && *stru.current_fd != STDOUT_FILENO
			&& *stru.current_fd != STDIN_FILENO)
			close(*stru.current_fd);
		if (open_chevron_fd(stru, info) == -1)
		{
			free(stru.start);
			free(stru.filename);
			return (-1);
		}
		free(stru.filename);
		if (*stru.current_fd == -1)
			break ;
		stru.next_chevron = get_next_chevron(stru.tmp);
	}
	free(stru.start);
	return (0);
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
