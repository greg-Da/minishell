/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:44:44 by gdalmass          #+#    #+#             */
/*   Updated: 2025/06/23 12:17:29 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	here_doc_loop(int write_fd, char *delim)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("minishell: warning: here-document delimited by ");
			printf("end-of-file (wanted `%s')\n", delim);
			exit(0);
		}
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			exit(0);
		}
		ft_putendl_fd(line, write_fd);
		free(line);
	}
}

static int	wait_here_doc_child(int pid, int write_fd)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	waitpid(pid, &status, 0);
	close(write_fd);
	if (WIFSIGNALED(status))
	{
		int sig = WTERMSIG(status);
		if (sig == SIGINT)
		{
			if (g_is_in_execution == 2)
				return (130);
		}
	}
	return (0);
}

int	ft_here_doc(int write_fd, char *delim)
{
	pid_t	pid;
	int		ret;

	g_is_in_execution = 1;
	pid = fork();
	if (pid < 0)
		ft_error("fork failed");
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		here_doc_loop(write_fd, delim);
		setup_here_doc_signals();
	}
	ret = wait_here_doc_child(pid, write_fd);
	g_is_in_execution -= 1;
	return (ret);
}
