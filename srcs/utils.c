/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:46:30 by greg              #+#    #+#             */
/*   Updated: 2025/06/02 14:27:58 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *get_res_size(char *str)
{
    int i = 0;
    int len = 0;
    char quote_type = 0;
    char *result;

    if (!str)
        return NULL;
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

void free_pipes(char **pipes)
{
	int i = 0;
	if (!pipes)
		return;
	while (pipes[i])
		free(pipes[i++]);
	free(pipes);
}
