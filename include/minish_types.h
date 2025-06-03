/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:16:14 by quentin8340       #+#    #+#             */
/*   Updated: 2025/06/03 08:19:46 by quentin8340      ###   ########.fr       */
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

#endif