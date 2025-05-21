/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:46:40 by dfeve             #+#    #+#             */
/*   Updated: 2025/05/21 13:52:36 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	main(int ac, char **av, char **envp)
{
	t_minish manager;

	(void)ac;
	(void)av;

	printf("TEST TO HANDLE : \n");
	printf("PLS CHECK : >a ls >b >>c >d\n");


	while (1)
		manager.last_ex_code = handle_cmd(envp, &manager);

}