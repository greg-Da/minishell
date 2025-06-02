/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:47:00 by dfeve             #+#    #+#             */
/*   Updated: 2025/06/02 16:42:45 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#include <fcntl.h>
#include <libft.h>
#include <limits.h>
#include <pipex.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct s_minish
{
	int last_ex_code;
	char *last_cmd;
	char **envp;
	int add_history;
	int nb_cmds;

} t_minish;

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
} t_token;

typedef struct s_tokenized
{
	int nb_cmds;
	char **split_input;
	t_token *tokens;
} t_tokenized;

typedef struct s_quotes
{
	char *input;
	char *open;
	char *close;

} t_quotes;

char **get_pipes(char *input, t_minish *manager);
int get_files(t_parser *info, int i, char **pipes);
char *extract_filename(char *tmp, char *next_chevron);
int handle_filename_error(char **pipes, int i, char *tmp, char *start);
int open_chevron_fd(char chevron, int *current_fd, char *filename, t_parser *info, int append);

int is_unclosed_quotes(char *input);
int parser(char **pipes, char **envp, int pipe_nb);
char *get_res_size(char *str);
void close_quotes(t_quotes *quotes, char **input);

int pwd(void);
void ft_env(t_pipex *pip);
void ft_echo(char **cmd);
void ft_cd(char **path);
int handle_cmd(char **envp, t_minish *manager);
char *get_input(char *prompt, t_minish *manager);
void init_signals(void);
void handle_sigint(int sig);
char *expand_variable(char *var_name);
char	*expand_string(char *input);
void expand_all_args(char **args);
char *display_exit_code(char *input, t_minish manager);
void ft_export(char ***envp, char *arg);
void ft_unset(char ***envp, char *arg);
char **ft_realloc_env(char **envp, char *new_entry);
extern sig_atomic_t is_in_execution;
int check_quotes(char **input, t_minish *manager);
int is_between_quotes(char *str, int index, char quote);
char *remove_quotes(char *str);
void free_pipes(char **pipes);

#endif