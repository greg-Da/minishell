/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:49:30 by greg              #+#    #+#             */
/*   Updated: 2025/06/02 12:56:37 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void write_quote_heredoc(int fd, char *line)
{
    char *tmp;

    tmp = ft_strjoin(line, "\n");
    if (write(fd, tmp, ft_strlen(tmp)) == -1)
    {
        free(tmp);
        free(line);
        ft_error("write failure");
    }
    free(tmp);
    free(line);
}

void ft_quote_heredoc(int fd, char quote_char)
{
    char *line;

    while (1)
    {
        line = readline("quote > ");
        if (!line)
            break;
        if (ft_strchr(line, quote_char))
        {
            write_quote_heredoc(fd, line);
            break;
        }
        write_quote_heredoc(fd, line);
    }
    close(fd);
}

static void read_quote_file(int fd, char **input, char *quote_open, char *cmd)
{
    char buffer[1000];
    int b_read;
    char *tmp;

    b_read = read(fd, buffer, 999);
    buffer[b_read] = '\0';
    tmp = ft_strjoin(quote_open, "\n");
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
}

void close_quotes(t_quotes *quotes, char **input)
{
    int fd;
    char *cmd;

    fd = open("quotes.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
    if (*quotes->open == '"')
        ft_quote_heredoc(fd, '"');
    else
        ft_quote_heredoc(fd, '\'');
    fd = open("quotes.txt", O_RDWR);
    cmd = ft_substr(*input, 0, ft_strlen(*input) - ft_strlen(quotes->open));
    read_quote_file(fd, input, quotes->open, cmd);
    free(cmd);
    close(fd);
    unlink("quotes.txt");
}

char *remove_quotes(char *str)
{
    int i;
    int j = 0;
    char *result;
    char quote_type;

    if (!str)
        return NULL;
    result = get_res_size(str);
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
    return (result);
}