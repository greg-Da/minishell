/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:50:26 by quentin           #+#    #+#             */
/*   Updated: 2025/06/02 15:46:14 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand_variable(char *var_name)
{
	char	*value = getenv(var_name);

	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}
void	expand_all_args(char **args)  
{
	int		i = 0;
	char	*expanded;

	while (args && args[i])
	{
		expanded = expand_string(args[i]);
		free(args[i]);
		args[i] = expanded;
		i++;
	}
}

char	*expand_string(char *input)
{
	char	result[1024] = {0};
	char	var_name[256];
	char	*var_value;
	int		i = 0, j = 0, k;

	while (input[i])
	{
		if (input[i] == '$' && (ft_isalpha(input[i + 1]) || input[i + 1] == '_'))
		{
			i++;
			k = 0;
			while (ft_isalnum(input[i]) || input[i] == '_')
				var_name[k++] = input[i++];
			var_name[k] = '\0';
			var_value = expand_variable(var_name);
			if (var_value)
			{
				ft_strlcat(result, var_value, sizeof(result));
				j += ft_strlen(var_value);
				free(var_value);
			}
		}
		else
			result[j++] = input[i++];
	}
	result[j] = '\0';
	return (ft_strdup(result));
}


