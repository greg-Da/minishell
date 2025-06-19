/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:29:13 by gdalmass          #+#    #+#             */
/*   Updated: 2025/06/19 13:21:05 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	display_err(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
}

void	default_std(int *std)
{
	dup2(std[0], STDIN_FILENO);
	dup2(std[1], STDOUT_FILENO);
	close(std[0]);
	close(std[1]);
}

void	handle_exec_fail(int *std, int i, t_pipex *pip, t_prev prev)
{
	default_std(std);
	(void)i;
	ft_invalid_cmd(pip, &prev);
	exit(pip->exit_code);
}

int	check_trailing_pipe(char *input, char **pipes)
{
	char	*trimmed;

	trimmed = ft_strtrim(input, " \f\t\n\r\v");
	if (trimmed[ft_strlen(trimmed) - 1] == '|')
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
