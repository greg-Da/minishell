/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:00:56 by qbaret            #+#    #+#             */
/*   Updated: 2025/06/18 16:19:27 by qbaret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*strip_quotes(char *str)
{
	int		len;
	char	*res;
	int		i;
	int		j;

	len = 0;
	i = 0;
	j = 0;
	while (str[i])
		if (str[i++] != '"' && str[i - 1] != '\'')
			len++;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] != '"' && str[i] != '\'')
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

int	is_unclosed_quotes(char *input)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (input[i])
	{
		if (input[i] == '\'' && double_quote == 0)
			single_quote = ft_abs(single_quote - 1);
		else if (input[i] == '"' && single_quote == 0)
			double_quote = ft_abs(double_quote - 1);
		i++;
	}
	if (single_quote || double_quote)
		return (1);
	return (0);
}

char	*first_quotes(char *a, char *b)
{
	if (a == NULL)
		return (b);
	if (b == NULL)
		return (a);
	if (a <= b)
		return (a);
	return (b);
}

int	check_quotes(char **input, t_minish *manager)
{
	char		*d_quotes;
	char		*s_quotes;
	t_quotes	quotes;

	(void)manager;
	s_quotes = ft_strchr(*input, '\'');
	d_quotes = ft_strchr(*input, '"');
	while (d_quotes || s_quotes)
	{
		quotes.open = first_quotes(s_quotes, d_quotes);
		quotes.close = ft_strchr(quotes.open + 1, *quotes.open);
		if (!quotes.close)
		{
			close_quotes(&quotes, input);
			return (1);
		}
		s_quotes = ft_strchr(quotes.close + 1, '\'');
		d_quotes = ft_strchr(quotes.close + 1, '"');
	}
	return (0);
}

int	is_between_char(char *str, int index, char quote)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	while (str[i] && i < index)
	{
		if (str[i] == quote)
			in_quote = !in_quote;
		i++;
	}
	return (in_quote);
}
