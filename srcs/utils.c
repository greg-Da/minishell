/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:46:30 by greg              #+#    #+#             */
/*   Updated: 2025/06/16 13:38:45 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_between_any_quotes(char *str, int i)
{
	return (is_between_char(str, i, '\'') || is_between_char(str, i, '"'));
}

char	*get_res_size(char *str)
{
	int		i;
	int		len;
	char	quote_type;
	char	*result;

	i = 0;
	len = 0;
	quote_type = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (!quote_type && (str[i] == '\'' || str[i] == '"'))
			quote_type = str[i];
		else if (quote_type && str[i] == quote_type)
			quote_type = 0;
		else
			len++;
		i++;
	}
	result = malloc(len + 1);
	return (result);
}

void	free_pipes(char **pipes)
{
	int	i;

	i = 0;
	if (!pipes)
		return ;
	while (pipes[i])
		free(pipes[i++]);
	free(pipes);
}

char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	char	*res;
	size_t	len1;
	size_t	len2;
	size_t	len3;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	res = malloc(len1 + len2 + len3 + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, len1 + 1);
	ft_strlcat(res, s2, len1 + len2 + 1);
	ft_strlcat(res, s3, len1 + len2 + len3 + 1);
	return (res);
}





