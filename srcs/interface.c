/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:43:26 by greg              #+#    #+#             */
/*   Updated: 2025/06/10 09:39:20 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int get_pipe_count(char *input)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '|' && is_between_char(input, i, '\'') == 0 && is_between_char(input, i, '"') == 0)
			count++;
		i++;
	}
	return (count);
}

static int handle_err_exit(char *input, char *start)
{
	int i;
	char *err;

	i = 0;

	if (!input[i])
		return (0);
	

	if (input[i] == '+' || input[i] == '-')
		i++;

	while (ft_isdigit(input[i]))
		i++;


	if (ft_isalpha(input[i]))
	{
		err = ft_strjoin("minishell: exit:", start + 4);
		free(input);
		input = ft_strjoin(err, ": numeric argument required\n");
		ft_putstr_fd(input, 2);

		free(start);
		free(input);
		exit(2);
	}

	if (input[i] != '\0')
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

static int handle_exit(char *input, t_minish *manager)
{
	char *tmp;
	int res;
	int err;

	if (!input)
	{
		if (manager->last_cmd)
			free(manager->last_cmd);
		write(1, "exit\n", 5);
		exit(0);
	}

	// printf("exit: |%s\n", input);

	tmp = expand_string(input, manager);
	tmp = remove_quotes(tmp);
	free(input);

	input = ft_strdup(tmp);
	free(tmp);

	tmp = ft_strtrim(input + 4, " \f\t\n\r\v");

	err = handle_err_exit(tmp, input);
	if (err > 0)
	{
		free(input);
		free(tmp);
		return (err);
	}

	res = ft_atoi(tmp) % 256;
	free(input);
	free(tmp);
	write(1, "exit\n", 5);
	if (manager->last_cmd)
		free(manager->last_cmd);
	exit(res);
}

static void maybe_add_history(char **input, t_minish *manager, int is_unclosed)
{
	if ((ft_strcmp(*input, manager->last_cmd) != 0 || ft_strchr(*input, '\n')) && !is_unclosed)
		add_history(*input);
	if (is_unclosed)
	{
		check_quotes(input, manager);
		add_history(*input);
	}
}

static char *get_input_line(t_minish *manager)
{
	char *input;

	input = readline("minishell > ");
	if (!input)
		handle_exit(NULL, manager);
	if (*input == '\0')
	{
		free(input);
		return (0);
	}
	return (input);
}

int handle_cmd(t_minish *manager)
{
	char *input;
	char **pipes;
	int code;
	int is_unclosed;

	pipes = NULL;
	input = get_input_line(manager);
	if (!input)
		return (0);
	is_unclosed = is_unclosed_quotes(input);
	maybe_add_history(&input, manager, is_unclosed);

	char *tmp = expand_string(input, manager);
	free(input);
	input = tmp;

	free(manager->last_cmd);
	manager->last_cmd = ft_strdup(input);
	input = sanitize_str(input);
	pipes = get_pipes(input, manager);
	if (strncmp(input, "exit", 4) == 0 && manager->nb_cmds == 1)
	{
		free_pipes(pipes);
		return (handle_exit(input, manager));
	}
	code = parser(pipes, manager, get_pipe_count(input));
	free_pipes(pipes);
	free(input);
	return (code);
}
