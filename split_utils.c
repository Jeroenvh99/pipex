/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 15:26:42 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/03/23 11:55:03 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<stddef.h>

int	skip_single(char *s, int i)
{
	while (s[i])
	{
		if (s[i] == 39)
			break ;
		else
			++i;
	}
	return (i);
}

int	skip_double(char *s, int i)
{
	while (s[i])
	{
		if (s[i] == 34)
			break ;
		else
			++i;
	}
	return (i);
}

int	skip_quotes(char ***s, int *quotes, int i)
{
	if (s[0][0][i] == 39)
	{
		++(*quotes);
		++s[0][0];
		i = skip_single(s[0][0], i);
	}
	if (s[0][0][i] == 34)
	{
		++(*quotes);
		++s[0][0];
		i = skip_double(s[0][0], i);
	}
	return (i);
}

int	skip_quotes_count(char *s, int i)
{
	if (s[i] == 39)
	{
		++i;
		i = skip_single(s, i);
		++i;
	}
	if (s[i] == 34)
	{
		++i;
		i = skip_double(s, i);
		++i;
	}
	return (i);
}
