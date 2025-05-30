/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:32:12 by quentin8340       #+#    #+#             */
/*   Updated: 2025/05/30 11:45:14 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *first_quotes(char *a, char *b)
{
    if (a == NULL)
        return (b);
    if (b == NULL)
        return (a);

    if (a <= b)
        return a;
    return b;
}

char *check_quotes(char *input, t_quotes *quotes, t_minish *manager)
{
    char *d_quotes;
    char *s_quotes;
    int open;

    open = 0;
    s_quotes = ft_strchr(input, '\'');
    d_quotes = ft_strchr(input, '"');
    while (d_quotes || s_quotes)
    {
        open = 1;
        quotes->open = first_quotes(s_quotes, d_quotes);
        quotes->close = ft_strchr(quotes->open + 1, *quotes->open);
        if (!quotes->close)
            break;
        open = 0;
        s_quotes = ft_strchr(quotes->close + 1, '\'');
        d_quotes = ft_strchr(quotes->close + 1, '"');
    }
    if (open)
        return (here_doc());
    return (quotes);
}

char **get_pipes(char *input, t_minish *manager)
{
    t_quotes quotes;

    
}