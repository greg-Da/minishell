/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:32:12 by quentin8340       #+#    #+#             */
/*   Updated: 2025/06/02 16:02:52 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char **get_pipes_size(char *input, t_minish *manager)
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
    manager->nb_cmds = count + 1;
    pipes = malloc(sizeof(char *) * (manager->nb_cmds + 1));
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

char **get_pipes(char *input, t_minish *manager)
{
    char **pipes = get_pipes_size(input, manager);
    fill_pipes_array(pipes, input);
    return validate_pipes(pipes, input);
}
