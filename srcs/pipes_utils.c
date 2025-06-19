/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:25:33 by gdalmass          #+#    #+#             */
/*   Updated: 2025/06/19 14:45:01 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_trailing_pipe(char *input, char **pipes)
{
	char	*trimmed;

	trimmed = ft_strtrim(input, " \f\t\n\r\v");
	if (trimmed && *trimmed && trimmed[ft_strlen(trimmed) - 1] == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		free(pipes);
		free(trimmed);
		return (0);
	}
	free(trimmed);
	return (1);
}

char	**validate_pipes(char **pipes, char *input)
{
	if (!pipes)
	{
		free(input);
		return (NULL);
	}
	if (!pipes[0])
	{
		free_pipes(pipes);
		free(input);
		return (NULL);
	}
	return (pipes);
}
