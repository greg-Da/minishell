/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:44:44 by gdalmass          #+#    #+#             */
/*   Updated: 2025/06/05 14:04:13 by qbaret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_here_doc(int write_fd, char *delim)
{
	int		pid;
	int		status;
	char	*line;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			line = readline("> ");
			if (!line)
			{
                printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n",
		        delim);
				exit(0);
			}
            if(ft_strcmp(line, delim) == 0)
            {
                free(line);
                exit(0);
            }
			ft_putendl_fd(line, write_fd);
			free(line);
		}
	}
	else if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		signal(SIGINT, handle_sigint);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			write(1, "\n", 1);
			close(write_fd);
			unlink("here_doc.txt");
			return (1);
		}
	}
	return (0);
}
