/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:29:13 by gdalmass          #+#    #+#             */
/*   Updated: 2025/06/18 16:56:33 by qbaret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	display_err(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
}

void	ft_free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	count_args_inside(char *str, int *in_quote, char *quote, int *i)
{
	while (str[*i])
	{
		if (!*in_quote && (str[*i] == '\'' || str[*i] == '"'))
		{
			*in_quote = 1;
			*quote = str[(*i)++];
		}
		else if (*in_quote && str[*i] == *quote)
		{
			*in_quote = 0;
			(*i)++;
		}
		else if (!*in_quote && ft_is_space(str[*i]))
			break ;
		else
			(*i)++;
	}
}
