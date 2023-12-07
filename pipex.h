/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/07 12:37:34 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/03/23 11:56:31 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include"./libft/libft.h"

typedef struct s_info{
	int		index;
	int		offset;
	char	**paths;
	char	**comm_paths;
	char	**argv;
	char	***comm_argv;
}	t_info;

t_info	*init_state(char **argv, char **envp, int argc);
int		read_heredoc(t_info *state);
void	free_state(t_info *state);
char	**get_paths(char **env);
char	*get_path(char **paths, char *command);
int		open_outfile(t_info *state);
int		skip_single(char *s, int i);
int		skip_double(char *s, int i);
int		skip_quotes(char ***s, int *quotes, int i);
int		skip_quotes_count(char *s, int i);
char	**split_args(char *s, char c);
int		exec_command(char **envp, int fd, t_info *state);

#endif
