/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:45:59 by greg              #+#    #+#             */
/*   Updated: 2025/06/19 15:05:18 by qbaret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*extract_arg(char *str, int len)
{
	char	*arg;
	int		j;

	arg = malloc(len + 1);
	j = 0;
	if (!arg)
		return (NULL);
	while (j < len)
	{
		arg[j] = str[j];
		j++;
	}
	arg[j] = '\0';
	return (arg);
}

int	get_arg_length(char *str)
{
	int		in_quote;
	char	quote;
	int		i;

	in_quote = 0;
	quote = 0;
	i = 0;
	while (str[i])
	{
		if (!in_quote && (str[i] == '\'' || str[i] == '"'))
		{
			in_quote = 1;
			quote = str[i++];
		}
		else if (in_quote && str[i] == quote)
		{
			in_quote = 0;
			i++;
		}
		else if (!in_quote && ft_is_space(str[i]))
			break ;
		else
			i++;
	}
	return (i);
}

int	fill_args_array(char *str, char **args)
{
	int	arg_idx;
	int	len;

	arg_idx = 0;
	while (*str)
	{
		while (ft_is_space(*str))
			str++;
		if (!*str)
			break ;
		len = get_arg_length(str);
		args[arg_idx] = extract_arg(str, len);
		if (!args[arg_idx])
			return (0);
		str += len;
		arg_idx++;
	}
	args[arg_idx] = NULL;
	return (1);
}

int	count_args(char *str)
{
	int		i;
	int		count;
	int		in_quote;
	char	quote;

	in_quote = 0;
	quote = 0;
	count = 0;
	i = 0;
	while (str[i])
	{
		while (ft_is_space(str[i]))
			i++;
		if (!str[i])
			break ;
		count++;
		count_args_inside(str, &in_quote, &quote, &i);
	}
	return (count);
}

char	**split_args_preserving_quotes(char *str)
{
	char	**args;
	int		in_count;

	in_count = count_args(str);
	args = malloc(sizeof(char *) * (in_count + 1));
	if (!args)
		return (NULL);
	if (!fill_args_array(str, args))
	{
		free_args(args);
		return (NULL);
	}
	return (args);
}
