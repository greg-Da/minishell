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

char *skip_redir_and_filename(char *str)
{
    int i = 0, j = 0;
    char quote_char = 0;
	char chevron;
    char *res = malloc(strlen(str) + 1); // TEMPO

    if (!res)
        return NULL;

    while (str[i])
    {
        while (str[i] && ft_include(str[i], " \t\n\r\v"))
            res[j++] = str[i++];

        if ((str[i] == '>' || str[i] == '<') && !is_between_any_quotes(str, i))
        {
            chevron = str[i++];
            if (str[i] == chevron)
                i++;
            while (str[i] && ft_include(str[i], " \t\n\r\v"))
                i++;
            if (str[i] == '\'' || str[i] == '"')
            {
                quote_char = str[i++];
                while (str[i] && str[i] != quote_char)
                    i++;
                if (str[i] == quote_char)
                    i++;
            }
            else
            {
                while (str[i] && !ft_include(str[i], " \t\n\r\v><"))
                    i++;
            }
            continue;
        }
        if (str[i])
            res[j++] = str[i++];
    }
    res[j] = '\0';
    free(str);
    return res;
}

void ft_echo(char **cmd)
{
	int new_line;
	int i;


	i = 0;
	new_line = check_new_line_flag(cmd, &i);
	while (check_new_line_flag(cmd, &i) == 0)
		;
	if (!cmd[1])
	{
		if (new_line)
			write(1, "\n", 1);
		return;
	}

	cmd[1] = skip_redir_and_filename(cmd[1]);
	cmd[1] = remove_quotes(cmd[1]);
	while (cmd[1][i])
	{
		ft_putchar_fd(cmd[1][i], 1);
		i++;
	}
	if (new_line)
		write(1, "\n", 1);
}
