/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:44:44 by gdalmass          #+#    #+#             */
/*   Updated: 2025/06/16 11:09:21 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_here_doc(int write_fd, char *delim, t_minish *manager)
{
	int		pid;
	int		status;
	char	*line;

	is_in_execution = 1;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, handle_sigint_heredoc);
		signal(SIGQUIT, SIG_IGN);
		is_in_execution = 2;
		while (1)
		{
			line = readline("> ");
			if (!line)
			{
				printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n",
					delim);
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
		is_in_execution = 0;
	}
	else if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		is_in_execution = 0;
		signal(SIGINT, handle_sigint);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			write(1, "\n", 1);
			close(write_fd);
			unlink("here_doc.txt");
			manager->last_ex_code = 130;
			return (1);
		}
	}
	return (0);
}
