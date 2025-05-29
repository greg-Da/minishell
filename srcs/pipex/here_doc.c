/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:44:44 by gdalmass          #+#    #+#             */
/*   Updated: 2025/05/29 19:11:02 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_get_here_doc_line(int fd, char *limiter)
{
	int		b_read;
	char	*buf;
	char	*end;

	buf = malloc(1000);
	// printf("[%s]\n", limiter);
	while (1)
	{
		write(STDOUT_FILENO, "quote > ", 8);
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
}

int	ft_here_doc(int fd, char *limiter)
{
	int	pipe_fd[2];
	int	pid;

	if (pipe(pipe_fd) == -1)
		ft_error("pipe failed");
	pid = fork();
	if (pid == -1)
		ft_error("fork failed");
	if (pid == 0)
	{
		ft_get_here_doc_line(pipe_fd[1], limiter);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], fd) == -1)
			ft_error("dup2 failure");
		close(pipe_fd[0]);
		waitpid(pid, NULL, 0);
	}
	return (pid);
}
