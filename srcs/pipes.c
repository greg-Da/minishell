/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:32:12 by quentin8340       #+#    #+#             */
/*   Updated: 2025/05/30 20:00:58 by greg             ###   ########.fr       */
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

int ft_quote_heredoc(int fd, char quote_char)
{
    int b_read;
    char *buf;
    char *tmp;

    buf = malloc(1000);
    if (!buf)
        return (-1);

    while (1)
    {
        write(STDOUT_FILENO, "quote > ", 8);
        b_read = read(STDIN_FILENO, buf, 999);
        if (b_read == -1)
            ft_error("read failure");
        buf[b_read] = '\0';

        char *end_quote = ft_strchr(buf, quote_char);
        if (end_quote)
        {
            tmp = ft_strjoin(buf, "\n");
            if (write(fd, tmp, b_read) == -1)
            {
                free(tmp);
                ft_error("write failure");
            }
            free(tmp);
            break;
        }

        if (b_read > 0)
        {
            tmp = ft_strjoin(buf, "\n");
            if (write(fd, tmp, b_read) == -1)
            {
                free(tmp);
                ft_error("write failure");
            }
            free(tmp);
        }
    }
    free(buf);
    close(fd);
    return (0);
}

void close_quotes(t_quotes *quotes, char **input)
{
    int fd;
    char *cmd;
    char buffer[1000];
    int b_read;
    char *tmp;


    fd = open("quotes.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
    if (*quotes->open == '"')
        ft_quote_heredoc(fd, '"');
    else
        ft_quote_heredoc(fd, '\'');

    open("quotes.txt", O_RDWR | O_CREAT | O_APPEND, 0644);


    b_read = read(fd, buffer, 999);
    // printf("b_read: %d\n", b_read);
    buffer[b_read] = '\0';

    tmp = ft_strjoin(quotes->open, "\n");
    cmd = ft_substr(*input, 0, ft_strlen(*input) - ft_strlen(quotes->open));

    while (b_read != 0)
    {
        free(*input);
        *input = ft_strjoin(tmp, buffer);
        free(tmp);
        b_read = read(fd, buffer, 999);
        buffer[b_read] = '\0';
        tmp = ft_strdup(*input);
    }
    free(tmp);
    tmp = ft_strjoin(cmd, *input);
    free(*input);
    *input = ft_strjoin(tmp, "\n");
    free(tmp);
    free(cmd);
    unlink("quotes.txt");
}

int check_quotes(char **input, t_minish *manager)
{
    char *d_quotes;
    char *s_quotes;
    t_quotes quotes;

    (void)manager;

    s_quotes = ft_strchr(*input, '\'');
    d_quotes = ft_strchr(*input, '"');

    printf("*input: %s\n", *input);

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

char **get_pipes(char *input)
{
    int i = 0, start = 0, count = 0;
    int j = 0;
    char **pipes = NULL;

    while (input[i])
    {
        if (input[i] == '|' && !(is_between_quotes(input, i, '"') || is_between_quotes(input, i, '\'')))
            count++;
        i++;
    }
    pipes = malloc(sizeof(char *) * (count + 2));
    if (!pipes)
        return NULL;

    i = 0;
    j = 0;
    while (input[i])
    {
        if (input[i] == '|' && !(is_between_quotes(input, i, '"') || is_between_quotes(input, i, '\'')))
        {
            pipes[j++] = ft_substr(input, start, i - start);
            start = i + 1;
        }
        i++;
    }
    // Last segment
    pipes[j++] = ft_substr(input, start, i - start);
    pipes[j] = NULL;
    return pipes;
}
