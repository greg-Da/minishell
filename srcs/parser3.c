/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:15:38 by greg              #+#    #+#             */
/*   Updated: 2025/05/29 18:05:55 by quentin8340      ###   ########.fr       */
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
	trimmed = ft_strtrim(str, " \t\n\v\f\r");
    free(str);
    if (!trimmed)
        return (NULL);
    return trimmed;
}

// char *get_chevron_indices(char *pipe, int index[2])
// {
//     char *chevron_in;
//     char *chevron_out;
//     char *last_chevron;

//     chevron_in = ft_strchr(pipe, '<');
//     chevron_out = ft_strchr(pipe, '>');
//     last_chevron = ft_strrchr(pipe, '>');  // Find last occurrence of '>'
    
//     if (chevron_in)
//         index[0] = chevron_in - pipe;
//     else
//         index[0] = 0;
//     if (chevron_out)
//         index[1] = last_chevron - pipe;  // Use last '>' position
//     else
//         index[1] = ft_strlen(pipe);

//     if (last_chevron)
//         return last_chevron;
//     return chevron_in;
// }