/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:50:26 by quentin           #+#    #+#             */
/*   Updated: 2025/06/18 11:09:14 by qbaret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand_variable(char *var_name, t_minish *manager)
{
	char	*value;
	int		i;

	i = -1;
	value = NULL;
	while (manager->envp[++i] != NULL)
	{
		if (ft_strncmp(manager->envp[i], var_name, ft_strlen(var_name)) == 0
			&& manager->envp[i][ft_strlen(var_name)] == '=')
		{
			value = manager->envp[i] + ft_strlen(var_name) + 1;
			break ;
		}
	}
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}
static int	handle_dollar_question(char *result, int j, t_minish *manager)
{
	char	*var_value;
	size_t	len;

	var_value = ft_itoa(manager->last_ex_code);
	if (var_value)
	{
		len = ft_strlen(var_value);
		if ((size_t)(j + len) < 2048)
			ft_strlcpy(result + j, var_value, 2048 - j);
		j += len;
		free(var_value);
	}
	return (j);
}

static int	handle_dollar_variable(char *input, int *i, char *result, int j,
		t_minish *manager)
{
	char	var_name[256];
	char	*var_value;
	size_t	len;
	int		k;

	k = 0;
	while ((ft_isalnum(input[*i]) || input[*i] == '_') && k < 255)
		var_name[k++] = input[(*i)++];
	var_name[k] = '\0';
	var_value = expand_variable(var_name, manager);
	if (var_value)
	{
		len = ft_strlen(var_value);
		if ((size_t)(j + len) < 2048)
			ft_strlcpy(result + j, var_value, 2048 - j);
		j += len;
		free(var_value);
	}
	return (j);
}

static int	handle_other_dollar_cases(char *input, int *i, char *result, int j)
{
	if ((size_t)(j + 1) < 2048)
		result[j++] = '$';
	if (input[*i] && (size_t)(j + 1) < 2048)
		result[j++] = input[(*i)++];
	return (j);
}

char	*expand_string(char *input, t_minish *manager)
{
	char	result[2048] = {0};
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '$' && !is_between_char(input, i, '\''))
		{
			i++;
			if (input[i] == '?')
				j = handle_dollar_question(result, j, manager), i++;
			else if (ft_isalpha(input[i]) || input[i] == '_')
				j = handle_dollar_variable(input, &i, result, j, manager);
			else
				j = handle_other_dollar_cases(input, &i, result, j);
		}
		else if ((size_t)(j + 1) < 2048)
			result[j++] = input[i++];
	}
	result[j] = '\0';
	return (ft_strdup(result));
}
