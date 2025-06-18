/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevron.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:08:00 by greg              #+#    #+#             */
/*   Updated: 2025/06/18 13:34:26 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parse_chevron_type(char **tmp, char chevron, t_parser *info, int *append)
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

static void	setup(t_chevron *stru, int i, int (*fd)[2])
{
	stru->start = stru->tmp;
	stru->next_chevron = get_next_chevron(stru->tmp);
	fd[i][0] = STDIN_FILENO;
	fd[i][1] = STDOUT_FILENO;
}

int	process_chevrons(char **pipes, int i, int (*fd)[2], t_parser *info)
{
	t_chevron	stru;

	stru.tmp = ft_strdup(pipes[i]);
	if (!stru.tmp)
		return (-1);
	setup(&stru, i, fd);
	while (stru.next_chevron)
	{
		if (get_filename(&stru, info) == -1)
			return (-1);
		if (!stru.filename[0])
		{
			free(stru.filename);
			return (handle_filename_error(pipes, i, stru.tmp, stru.start));
		}
		if (redir_to_file(&stru, fd, i, info) == -1)
			return (-1);
		if (*stru.current_fd == -1)
			break ;
		stru.next_chevron = get_next_chevron(stru.tmp);
	}
	free(stru.start);
	return (0);
}
