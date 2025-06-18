/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:16:14 by quentin8340       #+#    #+#             */
/*   Updated: 2025/06/18 13:12:00 by qbaret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_TYPES_H
# define MINISH_TYPES_H

typedef struct s_minish
{
	int		last_ex_code;
	char	*last_cmd;
	char	**envp;
	int		add_history;
	int		nb_cmds;
}			t_minish;

typedef struct s_input
{
	char	*input;
	int		*i;
}			t_input;

#endif