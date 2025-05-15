/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:36:57 by dfeve             #+#    #+#             */
/*   Updated: 2025/01/28 23:43:58 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	put_in_result(char **result, char *str)
{
	char	*tmp;

	tmp = NULL;
	if (!(*result))
	{
		*result = malloc(1);
		(*result)[0] = '\0';
	}
	if (!str)
		return (-1);
	tmp = ft_strjoin((const char *)(*result), (const char *)str);
	if (!tmp)
		return (-1);
	free(*result);
	*result = tmp;
	return (1);
}

static int	split_result(char **result, char **remainder)
{
	char	*tmp;
	char	*rtmp;
	char	*newline;

	if (!(*result))
		return (-1);
	newline = ft_strchr((const char *)(*result), '\n');
	if (newline)
	{
		tmp = ft_substr((const char *)(*result), 0, (newline - *result) + 1);
		rtmp = ft_strdup(newline + 1);
	}
	else
	{
		tmp = ft_strjoin(*result, *remainder);
		rtmp = NULL;
	}
	if (!tmp)
		return (-1);
	free(*result);
	*remainder = rtmp;
	*result = tmp;
	return (1);
}

static char	*return_base_func(int val, char **result,
							char **remainder, char **buffer)
{
	if (val > 0)
	{
		free(*buffer);
		if (split_result(result, remainder) < 0 || (*result)[0] == 0)
			return (return_base_func(-1, result, remainder, buffer));
		return (*result);
	}
	else
	{
		free(*result);
		return (NULL);
	}
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*buffer;
	char		*result;
	int			bt_read;

	result = remainder;
	remainder = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 2);
	if (!buffer)
		return (NULL);
	bt_read = 1;
	while (bt_read > 0)
	{
		bt_read = read(fd, buffer, BUFFER_SIZE);
		if (bt_read < 0)
			bt_read = 0;
		buffer[bt_read] = '\0';
		if (put_in_result(&result, buffer) < 0)
			return (return_base_func(-1, &result, &remainder, &buffer));
		if (ft_strchr((const char *)result, '\n') != NULL)
			break ;
	}
	return (return_base_func(1, &result, &remainder, &buffer));
}
