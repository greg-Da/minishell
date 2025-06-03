/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:43:26 by greg              #+#    #+#             */
/*   Updated: 2025/06/03 12:45:40 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_pipe_count(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '|' && is_between_quotes(input, i, '\'') == 0
				&& is_between_quotes(input, i, '"') == 0)
			count++;
		i++;
	}
	return (count);
}

static void	handle_exit(char *input, t_minish *manager)
{
	if (manager->last_cmd)
		free(manager->last_cmd);
	free(input);
	write(1, "exit\n", 5);
	exit(0);
}

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

	input = readline("find a funny name > ");
	if (!input)
		handle_exit(NULL, manager);
	if (*input == '\0')
	{
		free(input);
		return (0);
	}
	return (input);
}

int	handle_cmd(t_minish *manager)
{
	char	*input;
	char	**pipes;
	int		code;
	int		is_unclosed;

	pipes = NULL;
	input = get_input_line(manager);
	if (!input)
		return (0);
	is_unclosed = is_unclosed_quotes(input);
	maybe_add_history(&input, manager, is_unclosed);
	free(manager->last_cmd);
	manager->last_cmd = ft_strdup(input);
	input = sanitize_str(input);
	pipes = get_pipes(input, manager);
	// TO UPDATE EXIT
	if (strncmp(input, "exit", 4) == 0 && manager->nb_cmds == 1)
		handle_exit(input, manager);
	code = parser(pipes, manager, get_pipe_count(input));
	free_pipes(pipes);
	free(input);
	return (code);
}
