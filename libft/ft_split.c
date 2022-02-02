/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 14:41:53 by tjamis            #+#    #+#             */
/*   Updated: 2021/05/10 19:02:01 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

static size_t	get_size(char const *s, char c)
{
	size_t		size;

	size = 0;
	while (*s)
	{
		if (!size)
			size++;
		if (*s && *s == c)
		{
			while (*s && *s == c)
				s++;
			if (*s)
				size++;
			continue ;
		}
		s++;
	}
	return (size);
}

static size_t	get_len(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (s[count] && s[count] != c)
		count++;
	return (count);
}

static int	full_strs(char const *s, char c, size_t size, char	**result)
{
	size_t	count;
	size_t	size_word;

	count = 0;
	while (count < size - 1)
	{
		size_word = get_len(s, c) + 1;
		result[count] = malloc(size_word);
		if (!result[count])
		{
			size_word = 0;
			while (size_word < count)
				free(result[count]);
			free(result);
			return (0);
		}
		ft_strlcpy(result[count], s, size_word);
		s += size_word;
		while (*s == c)
			s++;
		count++;
	}
	result[count] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t	size;
	char	**result;

	if (!s)
		return (NULL);
	while (*s && *s == c)
		s++;
	size = get_size(s, c) + 1;
	result = (char **)malloc(sizeof(char *) * (size));
	if (!result || !full_strs(s, c, size, result))
		return (NULL);
	return (result);
}
