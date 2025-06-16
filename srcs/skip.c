/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:39:52 by quentin8340       #+#    #+#             */
/*   Updated: 2025/06/16 11:44:25 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	while (input[i])
	{
		if (((input[i] == '>' || input[i] == '<')
				&& !is_between_any_quotes(input, i)))
		{
			i++;
			if (input[i] == input[i - 1])
				i++;
			while (input[i] && ft_include(input[i], " \t\n\r\v"))
				i++;
			if (input[i] == '\'' || input[i] == '"')
				i = skip_quotes(input, i);
			else
			{
				while (input[i] && !ft_include(input[i], " \t\n\r\v><"))
					i++;
			}
			while (input[i] && ft_include(input[i], " \t\n\r\v"))
				i++;
			if (j > 0 && input[i] && res[j - 1] != ' ')
				res[j++] = ' ';
			continue ;
		}
		res[j++] = input[i++];
	}
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
