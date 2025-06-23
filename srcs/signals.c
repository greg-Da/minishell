/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:21:51 by quentin8340       #+#    #+#             */
/*   Updated: 2025/06/23 12:08:14 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

sig_atomic_t	g_is_in_execution = 0;

// g_is_in_execution = 0 // main process
// g_is_in_execution = 1 // child process

// g_is_in_execution = 2 // SIGINT
// g_is_in_execution = 4 // SIGQUIT
// g_is_in_execution = 6 // CTRL + /

// g_is_in_execution == 2 //  main process + SIGINT
// g_is_in_execution == 3 //  child process + SIGINT

// g_is_in_execution == 4 //  main process + SIGQUIT
// g_is_in_execution == 5 //  child process + SIGQUIT


void	handle_sigint(int sig)
{
    if (sig == SIGINT)
    {
        write(STDOUT_FILENO, "\n", 1);
        if (g_is_in_execution % 2 == 0)
        {
            rl_replace_line("", 0);
            rl_on_new_line();
            rl_redisplay();
            g_is_in_execution = 2;
        }
        else
            g_is_in_execution = 3;
    }
}

void	setup_here_doc_signals(void)
{
	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(1);
}

void	init_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
