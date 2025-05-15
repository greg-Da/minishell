/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:47:00 by dfeve             #+#    #+#             */
/*   Updated: 2025/05/15 14:30:31 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <fcntl.h>
# include <libft.h>
# include <limits.h>
# include <pipex.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_minish
{
	int		last_ex_code;
	char	*last_cmd;
}			t_minish;

typedef enum e_token
{
	INVALID = -1,
	WORD = 1,
	PIPE,
	AND,
	OR,
	VAR,
	QUOTE,
	D_QUOTE,
	R_DIR_OUT,
	R_DIR_IN,
	RR_DIR_OUT,
	RR_DIR_IN,
}			t_token;

typedef struct s_tokenized
{
	int		nb_cmds;
	char	**split_input;
	t_token	*tokens;
}			t_tokenized;

int			pwd(void);
void		ft_env(t_pipex *pip);
void		ft_echo(char **cmd);
void		ft_cd(char **path);
int			handle_cmd(char **envp, t_minish *manager);


#endif