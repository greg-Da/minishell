/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:21:58 by gdalmass          #+#    #+#             */
/*   Updated: 2025/05/29 17:31:30 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define VAR_FILE "t.txt"

# include "../../include/minish_types.h"

typedef struct s_minish	t_minish;

typedef struct s_pipex
{
	int					*pids;
	int					pids_size;
	int					fd[2];
	int (*fds)[2];
	char				**envp;
	char				**cmd_path;
	char				***cmd_args;
	int					cmd_count;
	int					exit;
	int					exit_code;
	t_minish			*manager;
}						t_pipex;

typedef struct s_prev
{
	int					in;
	int					out;
	int					i;
}						t_prev;

typedef struct s_split
{
	int					count;
	int					i;
	int					j;
}						t_custom_split;

typedef struct s_pip_quotes
{
	int					s_quotes;
	int					d_quotes;
}						t_pip_quotes;

typedef struct s_parser
{
	int					res;
	int (*fd)[2];
	int					index[2];
	char				*chevron;
	char				*files[2];
	char				**cmd;
	int					cmd_nb;

	int					here_doc;
	t_minish			*manager;
}						t_parser;
typedef struct s_chevron
{
	char				*tmp;
	char				*start;
	char				*next_chevron;
	char				chevron;
	int					append;
	char				*filename;
	int					*current_fd;
}						t_chevron;

void					ft_cleanup(t_pipex *pipex);

void					ft_init_struct(t_pipex *pipex, int nmb, char **cmd,
							t_minish *manager);
int						ft_here_doc(int fd, char *limiter);
void					ft_error(char *str);
char					**ft_custom_split(char *s, char c, t_minish *manager);
char					**ft_free(char **arr, int j);
size_t					ft_next_occurence(char const *s, char c, int index);
char					*ft_remove_slash(char *str, int len);
int						ft_create_outfile(int here_doc, char *file);
void					ft_invalid_cmd(t_pipex *pipex, t_prev *prev);
void					ft_loop(t_pipex *pipex, t_prev *prev, char **envp);
int						pipex(int nmb, char **cmd, t_minish *manager,
							int (*fd)[2]);
int						exec_pipex(int cmd_index, t_parser *info,
							t_minish *manager);
void					init_parser_struct(t_parser *info, t_minish *manager,
							char **pipes, int pipe_nb);
char					*sanitize_str(char *str);
char					*get_chevron_indices(char *pipe, int index[2]);
int						get_outfile(t_parser *info, char **pipes, int i);
int						get_infile(t_parser *info, char **pipes, int i, int j);
int						is_builtins(char *str);
void					reset_parser_fds(t_parser *info);

#endif