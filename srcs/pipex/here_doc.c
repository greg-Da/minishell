/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:44:44 by gdalmass          #+#    #+#             */
/*   Updated: 2025/05/30 19:32:50 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_here_doc(int fd, char *limiter)
{
	int		b_read;
	char	*buf;
	char	*end;

	buf = malloc(1000);
	// printf("[%s]\n", limiter);
	while (1)
	{
		write(STDOUT_FILENO, "here_doc > ", 11);
		b_read = read(STDIN_FILENO, buf, 999);
		if (b_read == -1)
			ft_error("read failure");
		buf[b_read] = '\0';
		end = ft_strchr(buf, '\n');
		if (end && (end - buf) == ft_strlen(limiter) && ft_strncmp(buf, limiter,
				(end - buf)) == 0)
			break ;
		if (write(fd, buf, b_read) == -1)
			ft_error("write failure");
	}
	free(buf);
	close(fd);
	return (0);
}
