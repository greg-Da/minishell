/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevron2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:28:40 by greg              #+#    #+#             */
/*   Updated: 2025/06/19 16:15:00 by qbaret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*extract_filename(char *input)
{
	int		i;
	char	*res;
	char	*trimmed;

	i = 0;
	res = NULL;
	while (input[i])
	{
		if ((input[i] == '>' || input[i] == '<' || ft_include(input[i],
					" \f\t\n\r\v")) && !is_between_any_quotes(input, i))
			break ;
		i++;
	}
	trimmed = ft_strtrim(input, " \f\t\n\r\v");
	res = ft_substr(trimmed, 0, i);
	free(trimmed);
	return (remove_quotes(res));
}

int	handle_filename_error(char **pipes, int i, char *tmp, char *start)
{
	char	*next;

	next = tmp;
	while (*next && *next == ' ')
		next++;
	if (*next == '>' || *next == '<')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putchar_fd(*next, 2);
		ft_putstr_fd("'\n", 2);
	}
	else if (pipes[i + 1])
		display_err("|");
	else
		display_err("newline");
	free(start);
	return (-1);
}

static int	handle_redir_to(t_chevron *stru, t_parser *info)
{
	if (stru->append)
		*stru->current_fd = open(stru->filename, O_WRONLY | O_CREAT | O_APPEND,
				0644);
	else
		*stru->current_fd = open(stru->filename, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
	if (*stru->current_fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(stru->filename);
		info->manager->last_ex_code = 1;
		return (1);
	}
	return (0);
}

static int	handle_here_doc(t_chevron *stru)
{
	int	temp_fd;

	temp_fd = open("here_doc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp_fd == -1)
	{
		perror("open");
		return (-1);
	}
	if (ft_here_doc(temp_fd, stru->filename))
	{
		close(temp_fd);
		unlink("here_doc.txt");
		return (1);
	}
	close(temp_fd);
	*stru->current_fd = open("here_doc.txt", O_RDONLY);
	return (0);
}

int	open_chevron_fd(t_chevron stru, t_parser *info)
{
	if (stru.chevron == '>')
	{
		if (handle_redir_to(&stru, info))
			return (1);
	}
	else if (stru.chevron == '<')
	{
		if (info->here_doc)
		{
			if (handle_here_doc(&stru))
				return (1);
		}
		else
			*stru.current_fd = open(stru.filename, O_RDONLY);
		if (*stru.current_fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(stru.filename);
			return (-1);
		}
	}
	return (0);
}
