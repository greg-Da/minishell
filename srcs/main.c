/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:46:40 by dfeve             #+#    #+#             */
/*   Updated: 2025/06/18 13:23:57 by qbaret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	increment_shlvl(t_minish *manager)
{
	int		i;
	char	*tmp;
	char	*shlvl;

	shlvl = expand_string("$SHLVL", manager);
	if (shlvl[0] == '\0')
		ft_export(manager, "export SHLVL=1");
	i = ft_atoi(shlvl);
	free(shlvl);
	tmp = ft_itoa(i + 1);
	shlvl = ft_strjoin("export SHLVL=", tmp);
	free(tmp);
	ft_export(manager, shlvl);
	free(shlvl);
}

int	main(int ac, char **av, char **envp)
{
	t_minish	manager;
	int			i;

	(void)ac;
	(void)av;
	init_signals();
	manager.last_cmd = NULL;
	manager.last_ex_code = 0;
	i = -1;
	while (envp[++i])
		;
	manager.envp = malloc(sizeof(char *) * (i + 1));
	if (!manager.envp)
	{
		perror("malloc");
		return (EXIT_FAILURE);
	}
	i = -1;
	while (envp[++i])
	{
		manager.envp[i] = ft_strdup(envp[i]);
		if (!manager.envp[i])
		{
			perror("ft_strdup");
			return (EXIT_FAILURE);
		}
	}
	manager.envp[i] = NULL;
	increment_shlvl(&manager);
	while (1)
		manager.last_ex_code = handle_cmd(&manager);
}
