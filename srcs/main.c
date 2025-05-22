/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:46:40 by dfeve             #+#    #+#             */
/*   Updated: 2025/05/22 14:35:57 by qbaret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	main(int ac, char **av, char **envp)
{
	t_minish manager;

	(void)ac;
	(void)av;

	init_signals();
	manager.last_cmd = NULL;
	manager.last_ex_code = 0;


	while (1)
		manager.last_ex_code = handle_cmd(envp, &manager);
}
