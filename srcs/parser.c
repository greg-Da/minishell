/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:15:38 by greg              #+#    #+#             */
/*   Updated: 2025/05/19 19:19:47 by greg             ###   ########.fr       */
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

void get_cmd(t_parser *info, char **pipes, int i)
{
    char *first;
    char *cmd;

    first = get_next_chevron(pipes[i]);

    if (first)
    {
        cmd = ft_substr(pipes[i], 0, first - pipes[i]);
        if (!cmd)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        cmd = ft_strdup(pipes[i]);
        if (!cmd)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
    }

    info->cmd[i] = sanitize_str(cmd);
    if (!info->cmd[i])
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
}

int parser(char **pipes, char **envp, int pipe_nb)
{
	t_parser info;
	int i;
	int j;

	init_parser_struct(&info, pipes, pipe_nb);
	info.fd[0] = STDIN_FILENO;
	info.fd[1] = STDOUT_FILENO;
	i = 0;
	j = 0;
	
	while (pipes[i])
	{
		if (get_files(&info, i, pipes) == -1)
		{
			clean_handle_cmd(&info);
			return (2);
		}

		get_cmd(&info, pipes, i);
		j++;

		// Execute command immediately if it has redirections
		if (get_next_chevron(pipes[i]))
		{
			info.res = exec_pipex(j, &info, envp);
			j = 0;
		}
		i++;
	}

	// Execute remaining commands if any
	if (j > 0)
	{
		info.res = exec_pipex(j, &info, envp);
	}

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

	pipes = ft_split(input, '|');
	if (!pipes) // Handle split failure
	{
		free(input);
		return (1);
	}

	if (!pipes[0]) // Handle empty pipe array
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
