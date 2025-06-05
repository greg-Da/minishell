/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:46:30 by greg              #+#    #+#             */
/*   Updated: 2025/06/05 10:57:06 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int is_between_any_quotes(char *str, int i)
{
	if (is_between_quotes(str, i, '\'') || is_between_quotes(str, i, '"'))
		return (1);
	return (0);
}

char	*get_res_size(char *str)
{
	int		i;
	int		len;
	char	quote_type;
	char	*result;

	i = 0;
	len = 0;
	quote_type = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (!quote_type && (str[i] == '\'' || str[i] == '"'))
			quote_type = str[i];
		else if (quote_type && str[i] == quote_type)
			quote_type = 0;
		else
			len++;
		i++;
	}
	result = malloc(len + 1);
	return (result);
}

void	free_pipes(char **pipes)
{
	int	i;

	i = 0;
	if (!pipes)
		return ;
	while (pipes[i])
		free(pipes[i++]);
	free(pipes);
}
