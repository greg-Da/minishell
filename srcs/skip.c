/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:39:52 by quentin8340       #+#    #+#             */
/*   Updated: 2025/06/18 13:00:19 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*parse_str(char *input, char *res, int *i, int *j)
{
	while (input[*i])
	{
		if (((input[*i] == '>' || input[*i] == '<')
				&& !is_between_any_quotes(input, *i)))
		{
			(*i)++;
			if (input[*i] == input[*i - 1])
				(*i)++;
			while (input[*i] && ft_include(input[*i], " \t\n\r\v"))
				(*i)++;
			if (input[*i] == '\'' || input[*i] == '"')
				*i = skip_quotes(input, *i);
			else
				while (input[*i] && !ft_include(input[*i], " \t\n\r\v><"))
					(*i)++;
			while (input[*i] && ft_include(input[*i], " \t\n\r\v"))
				(*i)++;
			if (*j > 0 && input[*i] && res[*j - 1] != ' ')
				res[(*j)++] = ' ';
			continue ;
		}
		res[(*j)++] = input[(*i)++];
	}
	return (res);
}

char	*skip_redir_and_filename(char *str)
{
	int		i;
	int		j;
	char	*res;
	char	*input;

	res = malloc(strlen(str) + 1);
	i = 0;
	j = 0;
	if (!res)
		return (NULL);
	input = remove_space_before_redir(str);
	free(str);
	res = parse_str(input, res, &i, &j);
	if (j > 0 && res[j - 1] == ' ')
		j--;
	res[j] = '\0';
	free(input);
	return (res);
}

int	skip_quotes(char *input, int i)
{
	if (is_between_any_quotes(input, ++i))
	{
		while (input[i] && input[i] != '\'' && input[i] != '"')
			i++;
	}
	i++;
	if (input[i] == '\'' || input[i] == '"')
		return (skip_quotes(input, i));
	return (i);
}
