/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:15:38 by greg              #+#    #+#             */
/*   Updated: 2025/05/21 14:01:00 by greg             ###   ########.fr       */
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

int process_chevrons(char **pipes, int i, int *fd, char chevron)
{
	char *tmp;
	char *start;
	char *filename;
	char *next_chevron;
	int append;

	tmp = ft_strdup(pipes[i]);
	if (!tmp)
		return (-1);

	start = tmp;
	tmp = ft_strchr(tmp, chevron);
	if (!tmp)
	{
		free(start);
		return (0);
	}

	while (tmp)
	{
		append = 0;
		tmp++;

		if (*tmp == chevron)
		{
			append = 1;
			tmp++;
		}

		while (*tmp && *tmp == ' ')
			tmp++;

		next_chevron = get_next_chevron(tmp);

		char *space = ft_strchr(tmp, ' ');
		if (space && (next_chevron == NULL || space < next_chevron))
			next_chevron = space;
		if (next_chevron)
		{
			filename = ft_substr(tmp, 0, next_chevron - tmp);
			if (!filename)
			{
				free(start);
				return (-1);
			}
		}
		else
		{
			filename = ft_strdup(tmp);
			if (!filename)
			{
				free(start);
				return (-1);
			}
		}

		char *trimmed = ft_strtrim(filename, " ");
		free(filename);
		filename = trimmed;

		if (!filename || filename[0] == '\0')
		{
			if (pipes[i + 1])
				ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", STDERR_FILENO);
			else
				ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", STDERR_FILENO);

			free(start);
			free(filename);
			printf("error\n");

			return (-1);
		}

		if (*fd != -1 && *fd != STDOUT_FILENO && *fd != STDIN_FILENO)
			close(*fd);

		if (chevron == '>')
		{
			if (append)
				*fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				*fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		else if (chevron == '<')
		{
			*fd = open(filename, O_RDONLY);
			if (*fd == -1)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				perror(filename);
				free(start);
				free(filename);
				return (-1);
			}
		}

		printf("fd : %d\n", *fd);
		printf("filename : %s\n", filename);

		free(filename);

		next_chevron = ft_strchr(tmp, chevron);
		if (!next_chevron)
			break;
		tmp = next_chevron;
	}

	free(start);
	return (0);
}

int get_files(t_parser *info, int i, char **pipes)
{
	if (process_chevrons(pipes, i, &info->fd[0], '<') == -1)
	{
		if (info->fd[0] != STDIN_FILENO)
			close(info->fd[0]);
		if (info->fd[1] != STDOUT_FILENO)
			close(info->fd[1]);
		return (-1);
	}
	if (process_chevrons(pipes, i, &info->fd[1], '>') == -1)
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

	while (*start)
	{
		if (*start == '>' || *start == '<')
		{
			start++;
			if (*start == '>' || *start == '<' || *start == ' ')
				start++;
			while (*start && *start != ' ' && *start != '>' && *start != '<')
				start++;
			while (*start && *start == ' ')
				start++;
		}
		else
			break;
	}

	if (*start)
	{
		// Find end of command (next redirection or end of string)
		end = start;
		while (*end && *end != '>' && *end != '<')
			end++;
		
		// Extract the command
		cmd = ft_substr(start, 0, end - start);
		if (!cmd)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		cmd = ft_strdup("");
	}

	info->cmd[j] = sanitize_str(cmd);
	if (!info->cmd[j])
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	// printf("command: '%s'\n", info->cmd[j]);
}

int parser(char **pipes, char **envp, int pipe_nb)
{
	t_parser info;
	int pipe_index;
	int cmd_index;

	init_parser_struct(&info, pipes, pipe_nb);
	info.fd[0] = STDIN_FILENO;
	info.fd[1] = STDOUT_FILENO;
	info.fd[2] = 0;

	pipe_index = 0;
	cmd_index = 0;

	while (pipes[pipe_index])
	{
		ft_strtrim(pipes[pipe_index], " ");

		if (get_files(&info, pipe_index, pipes) == -1)
		{
			clean_handle_cmd(&info);
			return (2);
		}

		get_cmd(&info, pipes[pipe_index], cmd_index);
		cmd_index++;

		// Execute command immediately if it has redirections
		if (ft_strchr(pipes[pipe_index], '>'))
		{
			info.res = exec_pipex(cmd_index, &info, envp);
			cmd_index = 0;
			info.fd[0] = STDIN_FILENO;
			info.fd[1] = STDOUT_FILENO;
			info.fd[2] = 0;
		}
		pipe_index++;
	}

	// Execute remaining commands if any
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
		return (0);

	if (*input == '\0')
	{
		free(input);
		return (0);
	}

	if (ft_strcmp(input, manager->last_cmd) != 0)
		add_history(input);

	
	ft_strtrim(input, " ");
	if (input[0] == '|' || input[ft_strlen(input)] == '|')
	{
		free(input);
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", STDERR_FILENO);
		return (2);
	}
	
	pipes = ft_split(input, '|');
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

	// Clean up
	i = 0;
	while (pipes[i])
		free(pipes[i++]);
	free(pipes);
	free(input);

	return (code);
}
