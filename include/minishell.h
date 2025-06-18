/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:47:00 by dfeve             #+#    #+#             */
/*   Updated: 2025/06/18 16:57:51 by qbaret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "minish_types.h"
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
int					open_chevron_fd(t_chevron stru, t_parser *info);

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
void				init_signals(void);
void				handle_sigint(int sig);
void				handle_sigint_heredoc(int sig);
void				setup_here_doc_signals(void);
char				*expand_variable(char *var_name, t_minish *manager);
char				*expand_string(char *input, t_minish *manager);
int					is_valid_identifier(const char *str);
int					ft_export(t_minish *manager, char *arg);
int					ft_unset(t_minish *manager, char *name);
char				**ft_realloc_env(char **envp, char *new_entry);
extern sig_atomic_t	g_is_in_execution;
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
char				*remove_space_before_redir(char *str);
int					skip_quotes(char *input, int i);
char				*ft_strjoin_three(char *s1, char *s2, char *s3);
int					get_filename(t_chevron *stru, t_parser *info);
int					get_files(t_parser *info, int i, char **pipes);
int					redir_to_file(t_chevron *stru, int (*fd)[2], int i,
						t_parser *info);
int					parse_chevron_type(char **tmp, char chevron, t_parser *info,
						int *append);
int					process_chevrons(char **pipes, int i, int (*fd)[2],
						t_parser *info);
int					handle_special(char **path, t_minish *manager, char *pwd);
int					handle_default(char **path, char *pwd, int status,
						t_minish *manager);
void				get_logical_parent(char *pwd, t_minish *manager);
int					get_home(t_minish *manager);
int					handle_go_back(char *cur, t_minish *manager);
void				update_pwd(char *pwd, char *old_pwd, t_minish *manager);
int					is_echo(const char *str);
int					handle_exit(char *input, t_minish *manager);
int					get_pipe_count(char *input);
void				display_err(char *str);
void				ft_free_array(char **arr);
void				free_args(char **args);
void				count_args_inside(char *str, int *in_quote, char *quote,
						int *i);
void				handle_exec_fail(int *std, int i, t_pipex *pip,
						t_prev prev);
void				default_std(int *std);
void				ft_exec(t_prev prev, t_pipex *pip, int i, char **envp);
#endif