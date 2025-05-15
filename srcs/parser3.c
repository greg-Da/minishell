/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:15:38 by greg              #+#    #+#             */
/*   Updated: 2025/03/10 16:51:01 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int is_builtins(char *str)
{
    if (!ft_strcmp(str, "pwd") || !ft_strcmp(str, "exit") || !ft_strcmp(str, "env")
    || !ft_strcmp(str, "cd") || !ft_strcmp(str, "echo") || !ft_strcmp(str, "export")
    || !ft_strcmp(str, "unset"))
		return (1);
    return (0);
}

char *sanitize_str(char *str)
{
    char *trimmed;
	
	if (!str)
		return (NULL);
	trimmed = ft_strtrim(str, " ");
    free(str);
    return trimmed;
}

char *get_chevron_indices(char *pipe, int index[2])
{
    char *chevron;

    chevron = ft_strchr(pipe, '<');
    if (chevron)
        index[0] = chevron - pipe;
    else
        index[0] = 0;
    chevron = ft_strchr(pipe, '>');
    if (chevron)
        index[1] = chevron - pipe;
    else
        index[1] = ft_strlen(pipe);
    return (chevron);
}
