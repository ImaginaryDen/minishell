/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_isspace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:25:43 by tjamis            #+#    #+#             */
/*   Updated: 2022/03/11 17:25:48 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace_s(char ch)
{
	if ((ch >= 9 && ch <= 13) || ch == 32)
		return (1);
	return (0);
}

static size_t	ft_count_words(char const *s)
{
	size_t	count;

	count = 0;
	while (s && *s)
	{
		while (ft_isspace_s(*s))
			s++;
		if (*s)
			count++;
		while (*s && !ft_isspace_s(*s))
			s++;
	}
	return (count);
}

static void	ft_free_words(char **words)
{
	char	**word;

	word = words;
	while (*word)
	{
		free(*word);
		word++;
	}
	free(words);
}

char	**split_isspace(char const *s)
{
	size_t	size;
	char	**words;

	if (!s)
		return (NULL);
	size = ft_count_words(s);
	words = ft_calloc(size + 1, sizeof(char *));
	if (!words)
		return (NULL);
	if (!ft_add_words(s, words))
		ft_free_words(words);
	return (words);
}
