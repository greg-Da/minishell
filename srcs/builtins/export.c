/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:13:26 by quentin8340       #+#    #+#             */
/*   Updated: 2025/05/29 19:13:52 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int is_valid_identifier(char *str)
{
	int i = 0;

	if (!str || !(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static void update_env(char ***envp, char *arg)
{
    int i = 0;
    size_t len = 0;

    while (arg[len] && arg[len] != '=')
    {
        if (arg[len] == ' ')
            return;
        len++;
    }
    while ((*envp)[i])
    {
		// printf("Checking env[%d]: %s\n", i, (*envp)[i]);
		// printf("Comparing with arg: %s\n", arg);
        if ((*envp)[i] != NULL && ft_strncmp((*envp)[i], arg, len) == 0 && (*envp)[i][len] == '=')
        {
            free((*envp)[i]);
            (*envp)[i] = ft_strdup(arg);
            return;
        }
        i++;
    }
    // Ajoute la nouvelle variable
    char **new_env = ft_realloc_env(*envp, arg);
    if (!new_env)
        return;
    // Libère l'ancien tableau
    i = 0;
    while ((*envp)[i])
        free((*envp)[i++]);
    free(*envp);
    *envp = new_env;
}

void ft_export(char ***envp, char *arg)
{
    if (!is_valid_identifier(arg))
        ft_putstr_fd("minishell: export: invalid identifier\n", 2);
    else
        update_env(envp, arg);
}
