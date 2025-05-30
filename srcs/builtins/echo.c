/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:32:37 by greg              #+#    #+#             */
/*   Updated: 2025/02/17 12:38:28 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int check_new_line_flag(char **cmd, int *i)
{
	int tmp;

	tmp = *i;
	if (!ft_strncmp("-n", &cmd[1][*i], 2))
	{
		*i += 2;
		while (cmd[1][*i] == 'n')
			(*i)++;
		if (cmd[1][*i] == '\0' || cmd[1][*i] == ' ')
		{
			while (cmd[1][*i] == ' ')
				(*i)++;
			return (0);
		}
		else
		{
			*i = tmp;
			return (1);
		}
	}
	return (1);
}

void ft_echo(char **cmd)
{
	int new_line;
	int i;

	i = 0;
	new_line = check_new_line_flag(cmd, &i);
	while (check_new_line_flag(cmd, &i) == 0)
		;
	cmd[1] = remove_quotes(cmd[1]);
	while (cmd[1][i])
	{
		ft_putchar_fd(cmd[1][i], 1);
		i++;
	}
	if (new_line)
		write(1, "\n", 1);
}
