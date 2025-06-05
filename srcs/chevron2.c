/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevron2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:28:40 by greg              #+#    #+#             */
/*   Updated: 2025/06/05 19:11:12 by qbaret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *extract_filename(char *input, char *next_chevron)
{
    int i = 0;
    char *trimmed;
    char *res;
    int start = 0;
    size_t limit = 0;

    trimmed = ft_strtrim(input, " \f\t\n\r\v");
    if (!trimmed)
        return (NULL);

    if (trimmed[0] == '<' || trimmed[0] == '>')
    {
        if (trimmed[1] == '>')
            start = 2;
        else
            start = 1;
    }
    if (next_chevron && next_chevron >= input)
        limit = (size_t)(next_chevron - input);
    else
        limit = 0;
    i = start;
    while (trimmed[i])
    {
        if (ft_include(trimmed[i], " \f\t\n\r\v") && !is_between_any_quotes(trimmed, i))
            break;
        if (limit && (size_t)(i + (input - trimmed)) >= limit)
            break;

        i++;
    }
    if (i <= start)
    {
        free(trimmed);
        return (NULL);
    }
    res = ft_substr(trimmed, start, i - start);
    free(trimmed);
    return (remove_quotes(res));
}



int handle_filename_error(char **pipes, int i, char *tmp, char *start)
{
	char *next;

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
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
					 2);
	free(start);
	return (-1);
}

int open_chevron_fd(char chevron, int *current_fd, char *filename,
					t_parser *info, int append)
{
	if (chevron == '>')
	{
		if (append)
			*current_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			*current_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (*current_fd == -1)
        {
            ft_putstr_fd("minishell: ", 2);
            perror(filename);
            info->manager->last_ex_code = 1;
            return (-1);
        }
	}
	else if (chevron == '<')
	{
		if (info->here_doc)
		{
			int temp_fd = open("here_doc.txt", O_WRONLY | O_CREAT | O_TRUNC,
							   0644);
			if (temp_fd == -1)
			{
				perror("open");
				return (-1);
			}
			if (ft_here_doc(temp_fd, filename))
			{
				close(temp_fd);
				return (-1);
			}
			close(temp_fd);
			*current_fd = open("here_doc.txt", O_RDONLY);
		}
		else
		{
			*current_fd = open(filename, O_RDONLY);
		}
		if (*current_fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(filename);
			return (-1);
		}
	}
	return (0);
}