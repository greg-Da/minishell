/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:32:12 by quentin8340       #+#    #+#             */
/*   Updated: 2025/05/30 15:16:32 by quentin8340      ###   ########.fr       */
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

int check_quotes(char **input, t_quotes *quotes, t_minish *manager)
{
    char *d_quotes;
    char *s_quotes;
    int fd;

    (void)manager;

    s_quotes = ft_strchr(*input, '\'');
    d_quotes = ft_strchr(*input, '"');

    printf("input: %s\n", *input);

    while (d_quotes || s_quotes)
    {
        quotes->open = first_quotes(s_quotes, d_quotes);
        quotes->close = ft_strchr(quotes->open + 1, *quotes->open);
        if (!quotes->close)
        {
            fd = open("here_doc.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
            if (*quotes->open == '"')
                ft_here_doc(fd, "\"");
            else
                ft_here_doc(fd, "'");

            char buffer[1000];
            int b_read = read(fd, buffer, 999);
            printf("b_read: %d\n", b_read);
            buffer[b_read] = '\0';

            while (b_read != 0)
            {
                printf("ICI\n");
                char *tmp = ft_strdup(*input);
                free(*input);
                *input = ft_strjoin(tmp, buffer);
                free(tmp);
                b_read = read(fd, buffer, 999);
                buffer[b_read] = '\0';
            }
            unlink("here_doc.txt");
            return (1);
        }
        s_quotes = ft_strchr(quotes->close + 1, '\'');
        d_quotes = ft_strchr(quotes->close + 1, '"');
    }
    return (0);
}

int is_quote(char c)
{
    return (c == '\'' || c == '"');
}

char **get_pipes(char *input, t_minish *manager)
{
    int i = 0, start = 0, idx = 0, count = 0;
    char quote_char = 0;
    int len = strlen(input);
    char **result = NULL;
    t_quotes quotes;

    while (i < len)
    {
        if (is_quote(input[i]))
        {
            quote_char = input[i];
            i++;
            while (i < len && input[i] != quote_char)
                i++;
        }
        else if (input[i] == '|')
        {
            count++;
        }
        i++;
    }
    count++;

    result = malloc(sizeof(char *) * (count + 1));
    if (!result)
        return NULL;

    i = 0;
    start = 0;
    idx = 0;
    quote_char = 0;
    while (i <= len)
    {
        if (i == len || (input[i] == '|' && quote_char == 0))
        {
            int seg_len = i - start;
            char *segment = malloc(seg_len + 1);
            if (!segment)
            {
                for (int j = 0; j < idx; j++)
                    free(result[j]);
                free(result);
                return NULL;
            }
            ft_strlcpy(segment, input + start, seg_len + 1);

            check_quotes(&segment, &quotes, manager);
            printf("%s\n", segment);

            result[idx++] = segment;
            start = i + 1;
        }
        else if (is_quote(input[i]))
        {
            if (quote_char == 0)
                quote_char = input[i];
            else if (quote_char == input[i])
                quote_char = 0;
        }
        i++;
    }
    result[idx] = NULL;

    return result;
}
