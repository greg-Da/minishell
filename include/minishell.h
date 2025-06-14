/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:47:00 by dfeve             #+#    #+#             */
/*   Updated: 2025/06/11 17:40:03 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "minish_types.h"
# include <fcntl.h>
# include <fcntl.h>
# include <libft.h>
# include <limits.h>
# include <pipex.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_quotes
{
	char			*input;
	char			*open;
	char			*close;

}					t_quotes;

char				**get_pipes(char *input, t_minish *manager);
int					get_files(t_parser *info, int i, char **pipes);
char				*extract_filename(char *tmp);
int					handle_filename_error(char **pipes, int i, char *tmp,
						char *start);
int					open_chevron_fd(char chevron, int *current_fd,
						char *filename, t_parser *info, int append);

int					is_unclosed_quotes(char *input);
int					parser(char **pipes, t_minish *manager, int pipe_nb);
char				*get_res_size(char *str);
void				close_quotes(t_quotes *quotes, char **input);

int					pwd(t_minish *manager);
int					is_path_missing(t_minish *manager);
void				ft_env(t_pipex *pip);
void				ft_echo(char **cmd);
int					ft_cd(char **path, t_minish *manager);
int					handle_cmd(t_minish *manager);
char				*get_input(char *prompt, t_minish *manager);
void				init_signals(void);
void				handle_sigint(int sig);
char				*expand_variable(char *var_name, t_minish *manager);
char				*expand_string(char *input, t_minish *manager);
void				expand_all_args(char **args, t_minish *manager);
int					is_valid_identifier(const char *str);
int					ft_export(t_minish *manager, char *arg);
int					ft_unset(t_minish *manager, char *name);
char				**ft_realloc_env(char **envp, char *new_entry);
extern				sig_atomic_t	is_in_execution;
int					check_quotes(char **input, t_minish *manager);
int					is_between_char(char *str, int index, char quote);
char				*remove_quotes(char *str);
void				free_pipes(char **pipes);
char				*strip_quotes(char *str);
int					set_env_key_value(t_minish *manager, char *key,
						char *value);
void				free_split(char **arr);
char				**split_args_preserving_quotes(char *str);

char				*get_next_chevron(char *str);
int					is_between_any_quotes(char *str, int i);
char				*skip_redir_and_filename(char *str);

#endif