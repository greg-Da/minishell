/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:46:30 by greg              #+#    #+#             */
/*   Updated: 2025/06/02 09:47:57 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int is_between_quotes(char *str, int index, char quote)
{
    int i;
    int in_quote;

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

char *remove_quotes(char *str)
{
    int i = 0;
    int j = 0;
    int len = 0;
    char *result;
    char quote_type = 0;

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
    if (!result)
        return NULL;

    i = 0;
    quote_type = 0;
    while (str[i])
    {
        if (!quote_type && (str[i] == '\'' || str[i] == '"'))
            quote_type = str[i];
        else if (quote_type && str[i] == quote_type)
            quote_type = 0;
        else
            result[j++] = str[i];
        i++;
    }
    result[j] = '\0';

    free(str);
    return result;
}
