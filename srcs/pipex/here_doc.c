/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:44:44 by gdalmass          #+#    #+#             */
/*   Updated: 2025/06/24 12:10:20 by gdalmass         ###   ########.fr       */
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

	waitpid(pid, &status, 0);
	signal(SIGINT, handle_sigint);
	close(write_fd);
	return (0);
}

int	ft_here_doc(int write_fd, char *delim)
{
	pid_t	pid;
	int		ret;
	int		tmp;

	tmp = *(g_is_in_execution());
	*(g_is_in_execution()) = 2;
	pid = fork();
	if (pid < 0)
		ft_error("fork failed");
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		setup_here_doc_signals();
		here_doc_loop(write_fd, delim);
	}
	ret = wait_here_doc_child(pid, write_fd);
	*(g_is_in_execution()) = tmp;
	return (ret);
}
