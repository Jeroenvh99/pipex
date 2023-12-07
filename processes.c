/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processes.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 13:38:41 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/03/23 11:21:58 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/wait.h>
#include<errno.h>
#include"pipex.h"

static void	child_process(int *tube, char **envp, int fd, t_info *state)
{
	if (dup2(fd, STDIN_FILENO) == -1 || close(fd) == -1)
		exit(errno);
	if (dup2(tube[1], STDOUT_FILENO) == -1 || close(tube[1]) == -1
		|| close(tube[0]) == -1)
		exit(errno);
	state->comm_argv[state->index] = split_args(state->argv[state->index
			+ state->offset], ' ');
	state->comm_paths[state->index] = get_path(state->paths,
			state->comm_argv[state->index][0]);
	execve(state->comm_paths[state->index], state->comm_argv[state->index],
		envp);
	exit(errno);
}

static void	child_process_last(char **envp, int fd, int *tube, t_info *state)
{
	int	outfd;

	if (close(tube[0]) == -1 || close(tube[1]) == -1)
		exit(errno);
	if (dup2(fd, STDIN_FILENO) == -1 || close(fd) == -1)
		exit(errno);
	outfd = open_outfile(state);
	if (dup2(outfd, STDOUT_FILENO) == -1 || close(outfd) == -1)
		exit(errno);
	state->comm_argv[state->index] = split_args(state->argv[state->index
			+ state->offset], ' ');
	state->comm_paths[state->index] = get_path(state->paths,
			state->comm_argv[state->index][0]);
	execve(state->comm_paths[state->index], state->comm_argv[state->index],
		envp);
	exit(errno);
}

static int	pipe_and_fork(t_info *state, int *tube)
{
	int	pid;

	if (pipe(tube) == -1)
	{
		perror("Pipe");
		free_state(state);
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Fork");
		free_state(state);
		exit(EXIT_FAILURE);
	}
	return (pid);
}

static void	parent_end(t_info *state, int child_id, int *tube)
{
	int	status;

	if (close(tube[0]) == -1)
	{
		free_state(state);
		exit(EXIT_FAILURE);
	}
	waitpid(child_id, &status, 0);
	free_state(state);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	exit(EXIT_FAILURE);
}

int	exec_command(char **envp, int fd, t_info *state)
{
	int		tube[2];
	pid_t	pid;

	pid = pipe_and_fork(state, tube);
	if (pid == 0)
	{
		if (state->argv[state->index + state->offset + 2])
			child_process(tube, envp, fd, state);
		else
			child_process_last(envp, fd, tube, state);
	}
	else if (state->argv[state->index + state->offset + 2])
	{
		if (close(tube[1]) == -1)
		{
			free_state(state);
			exit(EXIT_FAILURE);
		}
		++(state->index);
		exec_command(envp, tube[0], state);
	}
	parent_end(state, pid, tube);
	exit(EXIT_FAILURE);
}
