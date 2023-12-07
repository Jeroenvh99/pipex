/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 16:56:34 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/03/23 11:07:05 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include"pipex.h"

// static void	checkleaks()
// {
// 	system("leaks pipex");
// }

int	main(int argc, char **argv, char **envp)
{
	int		fd;
	t_info	*state;
	char	*error;

	if (argc < 5)
	{
		write(2, "not enough arguments\n", 21);
		return (1);
	}
	state = init_state(argv, envp, argc);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		state->offset = 3;
		fd = read_heredoc(state);
	}
	else
		fd = open(argv[1], O_RDONLY, 0644);
	if (fd == -1)
	{
		error = ft_strjoin("pipex: ", argv[1]);
		perror(error);
		free(error);
	}
	exec_command(envp, fd, state);
	return (1);
}
