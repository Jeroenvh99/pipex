/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 14:05:18 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/03/23 11:09:02 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include"pipex.h"

static void	init_comm_state(t_info *state, int argc)
{
	state->comm_paths = (char **)ft_calloc(argc - 2, sizeof(char *));
	if (!state->comm_paths)
	{
		write(2, "not enough memory available\n", 28);
		free_state(state);
		exit(EXIT_FAILURE);
	}
	state->comm_argv = (char ***)ft_calloc(argc - 2, sizeof(char **));
	if (!state->comm_argv)
	{
		write(2, "not enough memory available\n", 28);
		free_state(state);
		exit(EXIT_FAILURE);
	}
}

t_info	*init_state(char **argv, char **envp, int argc)
{
	t_info	*state;

	state = (t_info *)ft_calloc(1, sizeof(t_info));
	if (!state)
	{
		write(2, "not enough memory available\n", 28);
		exit(EXIT_FAILURE);
	}
	state->index = 0;
	state->offset = 2;
	state->argv = argv;
	state->paths = get_paths(envp);
	init_comm_state(state, argc);
	return (state);
}

static void	write_to_heredoc(char *delim, int fd)
{
	char	*line;

	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
}

int	read_heredoc(t_info *state)
{
	int		tube[2];
	char	*delim;

	if (pipe(tube) == -1)
	{
		perror("File descriptor");
		free_state(state);
		exit(EXIT_FAILURE);
	}
	delim = ft_strjoin(state->argv[2], "\n");
	write_to_heredoc(delim, tube[1]);
	free(delim);
	if (close(tube[1]) == -1)
	{
		perror("File descriptor");
		free_state(state);
		exit(EXIT_FAILURE);
	}
	return (tube[0]);
}
