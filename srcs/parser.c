/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:15:38 by greg              #+#    #+#             */
/*   Updated: 2025/05/30 13:29:21 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void clean_handle_cmd(t_parser *info)
{
	int j;

	j = -1;
	while (info->cmd[++j])
		free(info->cmd[j]);
	free(info->cmd);
	if (info->fd[0] != STDIN_FILENO)
		close(info->fd[0]);
	if (info->fd[1] != STDOUT_FILENO)
		close(info->fd[1]);

	info->fd[0] = STDIN_FILENO;
	info->fd[1] = STDOUT_FILENO;
	info->fd[2] = 0;
}

char *get_next_chevron(char *str)
{
	char *r_chev;
	char *l_chev;
	char *first;

	r_chev = ft_strchr(str, '>');
	l_chev = ft_strchr(str, '<');

	if (r_chev && l_chev)
	{
		if (r_chev < l_chev)
			first = r_chev;
		else
			first = l_chev;
	}
	else if (r_chev)
		first = r_chev;
	else if (l_chev)
		first = l_chev;
	else
		return (NULL);
	return (first);
}

int process_chevrons(char **pipes, int i, int fd[2])
{
	char *tmp;
	char *start;
	char *filename;
	char *next_chevron;
	int append;
	char chevron;

	tmp = ft_strdup(pipes[i]);
	if (!tmp)
		return (-1);

	start = tmp;
	next_chevron = get_next_chevron(tmp);
	while ((next_chevron))
	{
		chevron = *next_chevron;
		tmp = next_chevron;
		append = 0;
		tmp++;

		if (*tmp == chevron && chevron == '>')
		{
			printf("append\n");
			printf("tmp : %c\n", *tmp);
			append = 1;
			tmp++;
			printf("tmp : %c\n", *tmp);

		}

		while (*tmp && *tmp == ' ')
			tmp++;

		next_chevron = get_next_chevron(tmp);

		char *space = ft_strchr(tmp, ' ');
		if (space && (next_chevron == NULL || space < next_chevron))
			next_chevron = space;

		if (next_chevron)
			filename = ft_substr(tmp, 0, next_chevron - tmp);
		else
			filename = ft_strdup(tmp);

		if (!filename)
		{
			free(start);
			return (-1);
		}

		filename = sanitize_str(filename);
		if (!filename)
		{
			free(start);
			return (-1);
		}

		if (!filename || filename[0] == '\0')
		{
			char *next = tmp;
			if (*next == '>' || *next == '<')
				next++;
			
			while (*next && *next == ' ')
				next++;

			if (*next == '>' || *next == '<')
				ft_putstr_fd("minishell: syntax error near unexpected token `", 2),
					ft_putchar_fd(*next, 2),
					ft_putstr_fd("'\n", 2);
			else if (pipes[i + 1])
				ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
			else
				ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);

			free(start);
			free(filename);
			return (-1);
		}

		int *current_fd = NULL;

		current_fd = &fd[1];
		if (chevron == '<')
			current_fd = &fd[0];

		if (*current_fd != -1 && *current_fd != STDOUT_FILENO && *current_fd != STDIN_FILENO)
			close(*current_fd);

		if (chevron == '>')
		{
			if (append)
				*current_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				*current_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		else if (chevron == '<')
		{
			*current_fd = open(filename, O_RDONLY);
			if (*current_fd == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(filename);
				free(start);
				free(filename);
				return (-1);
			}
		}

		// printf("fd[%d] : %d\n", (chevron == '<' ? 0 : 1), *current_fd);
		// printf("filename : %s\n", filename);

		free(filename);

		if (*current_fd == -1)
			break;

		next_chevron = get_next_chevron(tmp);
	}

	free(start);
	return (0);
}

int get_files(t_parser *info, int i, char **pipes)
{
	if (process_chevrons(pipes, i, info->fd) == -1)
	{
		if (info->fd[0] != STDIN_FILENO)
			close(info->fd[0]);
		if (info->fd[1] != STDOUT_FILENO)
			close(info->fd[1]);
		return (-1);
	}
	return (1);
}

void get_cmd(t_parser *info, char *pipe, int j)
{
	char *cmd = NULL;
	char *start = pipe;
	char *end;
	char *part;

	while (*start)
	{
		while (*start && *start == ' ')
			start++;

		if (*start == '\0')
			break;

		if (*start == '>' || *start == '<')
		{
			start++;
			if (*start == '>' || *start == '<')
				start++;
			while (*start && *start == ' ')
				start++;
			while (*start && *start != ' ' && *start != '>' && *start != '<')
				start++;
			continue;
		}

		end = start;
		while (*end && *end != '>' && *end != '<')
			end++;

		part = ft_substr(start, 0, end - start);
		if (!part)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		if (cmd)
		{
			char *tmp = ft_strjoin(cmd, part);
			free(cmd);
			free(part);
			cmd = tmp;
		}
		else
		{
			cmd = part;
		}

		if (!cmd)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		start = end;
	}
	if (!cmd)
		cmd = ft_strdup("");
	info->cmd[j] = sanitize_str(cmd);
	if (!info->cmd[j])
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
}

int parser(char **pipes, char **envp, int pipe_nb)
{
	t_parser info;
	int pipe_index;
	int cmd_index;
	char *trimmed;

	init_parser_struct(&info, pipes, pipe_nb);
	info.fd[0] = STDIN_FILENO;
	info.fd[1] = STDOUT_FILENO;
	info.fd[2] = 0;

	pipe_index = 0;
	cmd_index = 0;

	while (pipes[pipe_index])
	{
		char *pipe_copy = ft_strdup(pipes[pipe_index]);
		if (!pipe_copy)
		{
			clean_handle_cmd(&info);
			return (1);
		}

		trimmed = sanitize_str(pipe_copy);
		if (!trimmed)
		{
			clean_handle_cmd(&info);
			return (1);
		}

		if (get_files(&info, pipe_index, pipes) == -1)
		{
			free(trimmed);
			clean_handle_cmd(&info);
			return (2);
		}

		get_cmd(&info, pipes[pipe_index], cmd_index);
		cmd_index++;

		if (ft_strchr(pipes[pipe_index], '>'))
		{
			info.res = exec_pipex(cmd_index, &info, envp);
			cmd_index = 0;
			info.fd[0] = STDIN_FILENO;
			info.fd[1] = STDOUT_FILENO;
			info.fd[2] = 0;
		}

		free(trimmed);
		pipe_index++;
	}

	if (cmd_index > 0)
		info.res = exec_pipex(cmd_index, &info, envp);

	clean_handle_cmd(&info);
	return (info.res);
}

int get_pipe_count(char *input)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '|')
			count++;
		i++;
	}
	return (count);
}

int handle_cmd(char **envp, t_minish *manager)
{
	char *input;
	char **pipes;
	int i;
	int code;

	input = readline(">  ");
	if (!input)
	{
		write(1, "exit\n", 5);
		if (manager->last_cmd)
			free(manager->last_cmd);
		exit(manager->last_ex_code);
	}

	if (*input == '\0')
	{
		free(input);
		return (0);
	}

	if (ft_strcmp(input, manager->last_cmd) != 0)
		add_history(input);

	input = sanitize_str(input);

	if (input[0] == '|' || input[ft_strlen(input)] == '|')
	{
		free(input);
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", STDERR_FILENO);
		return (2);
	}

	
	// check_if_between(strchr("| > < $"), check_q())

	pipes = get_pipes(input);

	// pipes = ft_split(input, '|');
	if (!pipes)
	{
		free(input);
		return (1);
	}

	if (!pipes[0])
	{
		free(pipes);
		free(input);
		return (0);
	}

	code = parser(pipes, envp, get_pipe_count(input));

	i = 0;
	while (pipes[i])
		free(pipes[i++]);
	free(pipes);
	free(input);

	return (code);
}
