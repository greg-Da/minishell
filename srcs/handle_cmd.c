/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:19:37 by qbaret            #+#    #+#             */
/*   Updated: 2025/06/19 15:50:48 by qbaret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	maybe_add_history(char **input, t_minish *manager, int is_unclosed)
{
	if ((ft_strcmp(*input, manager->last_cmd) != 0 || ft_strchr(*input, '\n'))
		&& !is_unclosed)
		add_history(*input);
	if (is_unclosed)
	{
		check_quotes(input, manager);
		add_history(*input);
	}
}

static char	*get_input_line(t_minish *manager)
{
	char	*input;

	(void)manager;
	g_is_in_execution = 0;
	input = readline("minishell > ");
	if (!input)
		handle_exit(NULL, manager);
	if (g_is_in_execution == 3)
		manager->last_ex_code = 130;
	if (*input == '\0')
	{
		free(input);
		return (0);
	}
	return (input);
}

int	handle_cmd_inside(t_minish *manager, char *input)
{
	int		code;
	char	**pipes;

	pipes = NULL;
	code = 0;
	pipes = get_pipes(input, manager);
	if (strncmp(input, "exit", 4) == 0 && manager->nb_cmds == 1)
	{
		free_pipes(pipes);
		return (handle_exit(input, manager));
	}
	g_is_in_execution = 1;
	if (pipes != NULL)
		code = parser(pipes, manager, get_pipe_count(input));
	g_is_in_execution = 0;
	if (code == 130)
	{
		free_pipes(pipes);
		free(input);
		return (130);
	}
	free_pipes(pipes);
	free(input);
	return (code);
}

int	handle_cmd(t_minish *manager)
{
	char	*input;
	int		is_unclosed;
	char	*tmp;

	input = get_input_line(manager);
	if (!input)
		return (0);
	is_unclosed = is_unclosed_quotes(input);
	maybe_add_history(&input, manager, is_unclosed);
	tmp = expand_string(input, manager);
	free(input);
	input = tmp;
	free(manager->last_cmd);
	manager->last_cmd = ft_strdup(input);
	input = sanitize_str(input);
	return (handle_cmd_inside(manager, input));
}
