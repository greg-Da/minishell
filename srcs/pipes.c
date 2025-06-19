/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:32:12 by quentin8340       #+#    #+#             */
/*   Updated: 2025/06/19 13:20:57 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**get_pipes_size(char *input, t_minish *manager)
{
	int		i;
	int		count;
	char	**pipes;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '|' && !(is_between_char(input, i, '"')
				|| is_between_char(input, i, '\'')))
			count++;
		i++;
	}
	manager->nb_cmds = count + 1;
	pipes = malloc(sizeof(char *) * (manager->nb_cmds + 1));
	if (!pipes)
		return (NULL);
	return (pipes);
}

int	check_empty_pipe(char *trimmed, char **pipes, int *j)
{
	if (*trimmed == '\0')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		pipes[(*j)++] = NULL;
		free_pipes(pipes);
		free(trimmed);
		return (0);
	}
	return (1);
}

int	handle_last_segment(char *input, t_pipes x, char **pipes)
{
	char	*segment;
	char	*trimmed;

	segment = ft_substr(input, x.start, x.i - x.start);
	trimmed = ft_strtrim(segment, " \f\t\n\r\v");
	free(segment);
	pipes[x.j++] = trimmed;
	pipes[x.j] = NULL;
	return (1);
}

static int	fill_pipes_array(char **pipes, char *input)
{
	t_pipes	x;
	char	*segment;
	char	*trimmed;

	x.i = 0;
	x.j = 0;
	x.start = 0;
	if (check_trailing_pipe(input, pipes) == 0)
		return (0);
	while (input[x.i])
	{
		if (input[x.i] == '|' && !(is_between_char(input, x.i, '"')
				|| is_between_char(input, x.i, '\'')))
		{
			segment = ft_substr(input, x.start, x.i - x.start);
			trimmed = ft_strtrim(segment, " \f\t\n\r\v");
			free(segment);
			if (check_empty_pipe(trimmed, pipes, &x.j) == 0)
				return (0);
			pipes[x.j++] = trimmed;
			x.start = x.i + 1;
		}
		x.i++;
	}
	return (handle_last_segment(input, x, pipes));
}

char	**get_pipes(char *input, t_minish *manager)
{
	char	**pipes;

	pipes = get_pipes_size(input, manager);
	if (fill_pipes_array(pipes, input) == 0)
		return (NULL);
	return (validate_pipes(pipes, input));
}
