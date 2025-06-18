/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:43:26 by greg              #+#    #+#             */
/*   Updated: 2025/06/18 15:26:44 by qbaret           ###   ########.fr       */
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
		if (input[i] == '|' && is_between_char(input, i, '\'') == 0)
			if (is_between_char(input, i, '"') == 0)
				count++;
		i++;
	}
	return (count);
}

static int	handle_err_exit(char *input, char *start)
{
	int		i;
	char	*err;

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
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2));
	return (0);
}

static int	handle_exit_inside(char *input, t_minish *manager)
{
	int		err;
	char	*tmp;
	int		res;

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

int	handle_exit(char *input, t_minish *manager)
{
	if (!input)
	{
		if (manager->last_cmd)
			free(manager->last_cmd);
		write(1, "exit\n", 5);
		exit(0);
	}
	return (handle_exit_inside(input, manager));
}






