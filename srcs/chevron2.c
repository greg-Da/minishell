/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevron2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:28:40 by greg              #+#    #+#             */
/*   Updated: 2025/06/11 17:35:14 by quentin8340      ###   ########.fr       */
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
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
			2);
	free(start);
	return (-1);
}

int	open_chevron_fd(char chevron, int *current_fd, char *filename,
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
			return (1);
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