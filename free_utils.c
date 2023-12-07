/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/07 13:11:32 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/03/23 11:04:57 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include"pipex.h"

static void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		++i;
	}
	free(arr);
	arr = NULL;
}

static void	free_split_array(char ***split_arr)
{
	int	i;

	i = 0;
	while (split_arr[i])
	{
		free_split(split_arr[i]);
		++i;
	}
	free(split_arr);
}

void	free_state(t_info *state)
{
	if (state->paths)
		free_split(state->paths);
	if (state->comm_paths)
		free_split(state->comm_paths);
	if (state->comm_argv)
		free_split_array(state->comm_argv);
	free(state);
}
