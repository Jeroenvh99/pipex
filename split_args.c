/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/20 19:07:33 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/03/23 11:57:22 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include"pipex.h"

static int	getarrlength(char *s, char dlm)
{
	int		i;
	int		count;
	char	prevc;

	i = 0;
	count = 0;
	prevc = dlm;
	while (*s)
	{
		i = skip_quotes_count(s, i);
		prevc = s[i - 1];
		if (s[i] == dlm && prevc != dlm)
			++count;
		prevc = s[i];
		if (!s[i])
			break ;
		++i;
	}
	if (prevc != dlm)
		++count;
	return (count);
}

static char	*getsplit(char **s, char dlm)
{
	int		i;
	int		quotes;
	char	prevc;
	char	*split;

	i = 0;
	quotes = 0;
	prevc = dlm;
	while (i == 0 || s[0][i - 1])
	{
		i = skip_quotes(&s, &quotes, i);
		prevc = s[0][i];
		++i;
		if ((s[0][i] == dlm && prevc != dlm) || (!(s[0][i])
			&& prevc != dlm))
		{
			split = ft_substr(s[0], 0, i - quotes);
			if (!split)
				return (NULL);
			s[0] += i;
			return (split);
		}
	}
	return (NULL);
}

static void	freearr(char **arr, int i)
{
	--i;
	while (i >= 0)
	{
		free(arr[i]);
		arr[i] = NULL;
		--i;
	}
	free(arr);
	arr = NULL;
}

char	**split_args(char *s, char c)
{
	int		arrsize;
	int		i;
	char	**arr;

	if (!s)
		return (NULL);
	arrsize = getarrlength(s, c) + 1;
	arr = ft_calloc(arrsize, sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < arrsize - 1)
	{
		while (*s == c)
			++s;
		arr[i] = getsplit(&s, c);
		if (!arr[i])
		{
			freearr(arr, i);
			return (NULL);
		}
		++i;
	}
	return (arr);
}
