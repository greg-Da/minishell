/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevron.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:08:00 by greg              #+#    #+#             */
/*   Updated: 2025/06/03 08:20:36 by quentin8340      ###   ########.fr       */
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
	char	*r_chev;
	char	*l_chev;
	char	*first;

	r_chev = ft_strchr(str, '>');
	l_chev = ft_strchr(str, '<');
	if (r_chev && l_chev)
	{
		if (r_chev < l_chev)
			first = r_chev;
		else
			first = l_chev;
	}
	else if (r_chev)
		first = r_chev;
	else if (l_chev)
		first = l_chev;
	else
		return (NULL);
	return (first);
}

int	process_chevrons(char **pipes, int i, int fd[2], t_parser *info)
{
	char	*tmp;
	char	*start;
	char	*next_chevron;
	char	chevron;
	int		append;
	char	*filename;
	int		*current_fd;

	tmp = ft_strdup(pipes[i]);
	if (!tmp)
		return (-1);
	start = tmp;
	next_chevron = get_next_chevron(tmp);
	while (next_chevron)
	{
		chevron = *next_chevron;
		tmp = next_chevron + 1;
		append = 0;
		parse_chevron_type(&tmp, chevron, info, &append);
		next_chevron = get_next_chevron(tmp);
		filename = extract_filename(tmp, next_chevron);
		if (!filename)
			return (free(start), -1);
		filename = sanitize_str(filename);
		if (!filename)
			return (free(start), -1);
		if (!filename[0])
		{
			free(filename);
			return (handle_filename_error(pipes, i, tmp, start));
		}
		current_fd = (chevron == '<') ? &fd[0] : &fd[1];
		if (*current_fd != -1 && *current_fd != STDOUT_FILENO
			&& *current_fd != STDIN_FILENO)
			close(*current_fd);
		if (open_chevron_fd(chevron, current_fd, filename, info, append) == -1)
		{
			free(start);
			free(filename);
			return (-1);
		}
		free(filename);
		if (*current_fd == -1)
			break ;
		next_chevron = get_next_chevron(tmp);
	}
	free(start);
	return (0);
}

int	get_files(t_parser *info, int i, char **pipes)
{
	if (process_chevrons(pipes, i, info->fd, info) == -1)
	{
		if (info->fd[0] != STDIN_FILENO)
			close(info->fd[0]);
		if (info->fd[1] != STDOUT_FILENO)
			close(info->fd[1]);
		return (-1);
	}
	return (1);
}
