/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:50:26 by quentin           #+#    #+#             */
/*   Updated: 2025/06/19 10:53:09 by qbaret           ###   ########.fr       */
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

static int	handle_dollar(t_input input, char *result, int j, t_minish *manager)
{
	char	var_name[256];
	char	*var_value;
	size_t	len;
	int		k;

	k = 0;
	while ((ft_isalnum(input.input[*input.i]) || input.input[*input.i] == '_')
		&& k < 255)
		var_name[k++] = input.input[(*input.i)++];
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

char	*expand_string(char *input, t_minish *m)
{
	char	result[2048];
	int		i[2];

	i[0] = 0;
	i[1] = 0;
	while (input[i[0]])
	{
		if (input[i[0]] == '$' && !is_between_char(input, i[0], '\''))
		{
			i[0]++;
			if (input[i[0]] == '?')
			{
				i[1] = handle_dollar_question(result, i[1], m);
				i[0]++;
			}
			else if (ft_isalpha(input[i[0]]) || input[i[0]] == '_')
				i[1] = handle_dollar((t_input){input, &i[0]}, result, i[1], m);
			else
				i[1] = handle_other_dollar_cases(input, &i[0], result, i[1]);
		}
		else if ((size_t)(i[1] + 1) < 2048)
			result[i[1]++] = input[i[0]++];
	}
	result[i[1]] = '\0';
	return (ft_strdup(result));
}
