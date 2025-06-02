/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:32:12 by quentin8340       #+#    #+#             */
/*   Updated: 2025/06/02 12:53:01 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char **get_pipes_size(char *input)
{
    int i = 0;
    int count = 0;
    char **pipes;

    while (input[i])
    {
        if (input[i] == '|' && !(is_between_quotes(input, i, '"') || is_between_quotes(input, i, '\'')))
            count++;
        i++;
    }
    pipes = malloc(sizeof(char *) * (count + 2));
    if (!pipes)
        return NULL;
    return (pipes);
}

static void fill_pipes_array(char **pipes, char *input)
{
    int i = 0, j = 0, start = 0;
    while (input[i])
    {
        if (input[i] == '|' && !(is_between_quotes(input, i, '"') || is_between_quotes(input, i, '\'')))
        {
            pipes[j++] = ft_substr(input, start, i - start);
            start = i + 1;
        }
        i++;
    }
    pipes[j] = ft_substr(input, start, i - start);
    pipes[++j] = NULL;
}

static char **validate_pipes(char **pipes, char *input)
{
    if (!pipes)
    {
        free(input);
        return NULL;
    }
    if (!pipes[0])
    {
        free_pipes(pipes);
        free(input);
        return NULL;
    }
    return pipes;
}

char **get_pipes(char *input)
{
    char **pipes = get_pipes_size(input);
    fill_pipes_array(pipes, input);
    return validate_pipes(pipes, input);
}

